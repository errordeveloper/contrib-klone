#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <klone/klone.h>
#include <klone/debug.h>
#include <klone/config.h>
#include <klone/server.h>
#include <klone/os.h>
#include "conf.h"
#include "context.h"
#include "main.h"

static context_t c;
context_t  *ctx = &c; /* exported */

#ifdef OS_WIN
    /* Win32 service name and description */
    enum { SS_NAME_BUFSZ = 64, SS_DESC_BUFSZ = 256 };
    static char ss_name[SS_NAME_BUFSZ] = "kloned";
    static char ss_desc[SS_DESC_BUFSZ] = "kloned daemon";

    int InstallService(); 
    int RemoveService();
#endif

static void usage()
{
    fprintf(stderr, 
        "Usage: server [-f config_file] [-d]                    \n"
        "          -d                    turn on debugging      \n"
        "          -F                    run in foreground      \n"
        #ifdef OS_WIN
        "          -i                    install service        \n"
        "          -u                    remove service         \n"
        #endif
        "          -f config_file        use config file        \n"
        );

    exit(1);
}

static int parse_opt(int argc, char **argv)
{
    int ret, len;
    #ifdef OS_WIN
        #define CMDLINE_FORMAT "hFdiuf:"
    #else
        #define CMDLINE_FORMAT "hFdf:"
    #endif

    dbg("argc: %d", argc);

    /* set defaults */
    ctx->daemon++;

    while((ret = getopt(argc, argv, CMDLINE_FORMAT)) != -1)
    {
        switch(ret)
        {
        case 'f':   /* source a config file */
            ctx->ext_config = u_strdup(optarg);
            dbg_err_if(ctx->ext_config == NULL);
            dbg("ext config: %s", ctx->ext_config);
            break;

        case 'd':   /* turn on debugging */
            ctx->debug++;
            break;

        case 'F':   /* run in foreground (not as a daemon/service) */
            ctx->daemon = 0;
            break;

        #ifdef OS_WIN
        case 'i':   /* install kloned service and exit */
            ctx->serv_op = SERV_INSTALL;
            break;

        case 'u':   /* uninstall kloned service and exit */
            ctx->serv_op = SERV_REMOVE;
            break;

        #endif

        default:
        case 'h': 
            usage();
        }
    }

    ctx->narg = argc - optind;
    ctx->arg = argv + optind;

    return 0;
err:
    return ~0;
}

#if defined(OS_WIN)

/* install the service with the service manager. after successful installation
   you can run the service from ControlPanel->AdminTools->Services */
int InstallService() 
{
    SC_HANDLE hSCM, hService;
    char szModulePathname[_MAX_PATH];
    SERVICE_DESCRIPTION sd = { ss_desc };
    int rc;

    // Open the SCM on this machine.
    hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);

    dbg_err_if(hSCM == NULL);

    dbg_err_if(GetModuleFileName(GetModuleHandle(NULL), szModulePathname, 
        _MAX_PATH) == 0 );

    /* add this service to the SCM's database */
    hService = CreateService(hSCM, ss_name, ss_name,
        SERVICE_CHANGE_CONFIG, SERVICE_WIN32_OWN_PROCESS, 
        SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE,
        szModulePathname, NULL, NULL, NULL, NULL, NULL);

    dbg_err_if(hService == NULL);

    rc = ChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &sd);

    dbg_err_if(rc == 0);

    /* success */
    MessageBox(NULL, "Service installation succeded", ss_name, MB_OK);

    return 0; 
err:
    /* common error handling */
    dbg_strerror(GetLastError());
    MessageBox(NULL, "Service installation error", ss_name, MB_OK);
    return ~0;
}


/* uninstall this service from the system */
int RemoveService() 
{
    SC_HANDLE hSCM, hService;
    int rc;

    hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);

    dbg_err_if(hSCM == NULL);

    /* Open this service for DELETE access */
    hService = OpenService(hSCM, ss_name, DELETE);

    dbg_err_if(hService == NULL);

    /* Remove this service from the SCM's database */
    rc = DeleteService(hService);

    dbg_err_if(rc == 0);

    /* success */
    MessageBox(NULL, "Uninstall secceded", ss_name, MB_OK);
    return 0;
err:
    /* common error handling */
    dbg_strerror(GetLastError());
    MessageBox(NULL, "Uninstall failed", ss_name, MB_OK);
    return ~0;
}

/* this function will be called by the SCM to request an action */
DWORD WINAPI HandlerEx(DWORD dwControl, DWORD dwEventType, 
        LPVOID lpEventData, LPVOID lpContext)
{
    enum { DENY_ACTION = 0xff };

    switch(dwControl)
    {
    case SERVICE_CONTROL_INTERROGATE:
        dbg("SERVICE_CONTROL_INTERROGATE" );
        SetServiceStatus(ctx->hServiceStatus, &ctx->status);
        return NO_ERROR;

    case SERVICE_CONTROL_STOP:
        dbg("SERVICE_CONTROL_STOP");

        if(ctx->status.dwCurrentState == SERVICE_STOPPED)
            return NO_ERROR; /* service already stopped */

        /* start the stop procedure, move to stop_pending state */
        ctx->status.dwCheckPoint = 1;
        ctx->status.dwWaitHint = 2000;
        ctx->status.dwCurrentState = SERVICE_STOP_PENDING; 
        SetServiceStatus(ctx->hServiceStatus, &ctx->status);

        server_stop(ctx->server);
        return NO_ERROR;

    case SERVICE_CONTROL_PAUSE:
        dbg("SERVICE_CONTROL_PAUSE");
        break;

    case SERVICE_CONTROL_CONTINUE:
        dbg("SERVICE_CONTROL_CONTINUE");
        break;

    case SERVICE_CONTROL_SHUTDOWN:
        dbg("SERVICE_CONTROL_SHUTDOWN");
        break;

    case SERVICE_CONTROL_PARAMCHANGE:
        dbg("SERVICE_CONTROL_PARAMCHANGE");
        break;

    default:
        dbg("SERVICE_CONTROL_UNKNOWN!!!!");
    }
    if(dwControl > 127 && dwControl < 255)
    {
        /* user defined control code */
        dbg("SERVICE_CONTROL_USER_DEFINED");
    } 
    return ERROR_CALL_NOT_IMPLEMENTED;
}

/* this is the main function of the service. when this function returns the
 * service will be terminated by the SCM */
void WINAPI ServiceMain(DWORD argc, PTSTR *argv)
{
    SERVICE_STATUS *pSt = &ctx->status;

    /* register the service with the ServiceControlManager */
    ctx->hServiceStatus = RegisterServiceCtrlHandlerEx(ss_name, HandlerEx, ctx);
    dbg_err_if( ctx->hServiceStatus == 0 );

    /* init the status struct and update the service status */
    ZeroMemory(pSt, sizeof(SERVICE_STATUS));
    /* just one service in this exe */
    pSt->dwServiceType = SERVICE_WIN32_OWN_PROCESS; 
    /* action supported by the service */
    pSt->dwControlsAccepted = SERVICE_ACCEPT_STOP;
    /* error returned while starting/stopping */
    pSt->dwWin32ExitCode = NO_ERROR;          
    /* service specific exit code */
    pSt->dwServiceSpecificExitCode = 0;          
    /* we're still initializing */
    pSt->dwCurrentState = SERVICE_START_PENDING;
    /* for progress operation */
    pSt->dwCheckPoint = 1;
    /* wait hint */
    pSt->dwWaitHint = 1000;
    /* set status */
    dbg_err_if(SetServiceStatus(ctx->hServiceStatus, pSt) == 0);

    dbg_err_if(parse_opt(argc, argv));

    /* load config and initialize */
    dbg_err_if(app_init());

    /* this should happen after initialization but I don't want to
       mess main.c with win32-only code */

    /* notify the end of initialization */
    dbg("SERVICE_RUNNING");
    ctx->status.dwCurrentState = SERVICE_RUNNING;
    ctx->status.dwCheckPoint = ctx->status.dwWaitHint = 0;    
    dbg_err_if(!SetServiceStatus(ctx->hServiceStatus, &ctx->status));

    /* run the main loop */
    app_run();

    /* let the service terminate */
    ctx->status.dwCurrentState = SERVICE_STOPPED;
    dbg_err_if(!SetServiceStatus(ctx->hServiceStatus, &ctx->status));

    return;

err:
    dbg_strerror(GetLastError());

    /* let the service terminate */
    ctx->status.dwCurrentState = SERVICE_STOPPED;
    dbg_err_if(!SetServiceStatus(ctx->hServiceStatus, &ctx->status));
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, 
    LPSTR lpCmdLine, int nCmdShow)
{
    SERVICE_TABLE_ENTRY ServiceTable[] = 
    {
        {   ss_name, ServiceMain }, 
        {   NULL, NULL }    /* end of list */
    };
    int rc = 0;
    const char *name, *desc;

    memset(ctx, 0, sizeof(context_t));

    /* parse command line parameters (and set ctx vars). NOTE: this work only 
       if launched by command line, for services see ServiceMain */
    dbg_err_if(parse_opt(__argc, __argv));

    if(ctx->serv_op)
    {
        /* load config and initialize */
        dbg_err_if(app_init());

        /* set up service name and description reading from the config file */
        name = config_get_subkey_value(ctx->config, "daemon.name");
        if(name)
            strncpy(ss_name, name, SS_NAME_BUFSZ);

        desc = config_get_subkey_value(ctx->config, "daemon.description");
        if(desc)
            strncpy(ss_desc, desc, SS_DESC_BUFSZ);

        if(ctx->serv_op == SERV_INSTALL)
            dbg_err_if(InstallService());
        else    
            dbg_err_if(RemoveService());
    } else if(ctx->daemon) {
        dbg("Starting in service mode...");
        /* StartServiceCtrlDispatcher does not return until the service 
           has stopped running...  */
        if(!StartServiceCtrlDispatcher(ServiceTable))
            dbg_strerror(GetLastError());
    } else {
        /* load config and initialize */
        dbg_err_if(app_init());

        rc = app_run();
    }

    dbg_err_if(app_term());

    return rc;
err:
    app_term();
    return ~0;
}

#elif defined(OS_UNIX)

int main(int argc, char **argv)
{
    int rc = 0;
    memset(ctx, 0, sizeof(context_t));

    /* parse command line parameters (and set ctx vars) */
    dbg_err_if(parse_opt(argc,argv));

    /* daemonize if not -F */
    if(ctx->daemon)
        dbg_err_if(daemon(0, 0));

    /* load config and initialize */
    dbg_err_if(app_init());

    /* jump to the main loop */
    rc = app_run();

    dbg_err_if(app_term());

    return rc;
err:
    app_term();
    return ~0;
}

#else
    #error unsupported platform
#endif



