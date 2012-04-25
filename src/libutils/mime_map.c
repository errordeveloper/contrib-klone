/*
 * Copyright (c) 2005-2012 by KoanLogic s.r.l. <http://www.koanlogic.com>
 * All rights reserved.
 *
 * This file is part of KLone, and as such it is subject to the license stated
 * in the LICENSE file which you have received as part of this distribution.
 *
 * $Id: mime_map.c,v 1.5 2006/01/09 12:38:38 tat Exp $
 */

#include <klone/mime_map.h>

mime_map_t mime_map[] = {
    /* extension    MIME type         0 or 1 (zippable or not) */
    { " ext not found ", "application/octet-stream",    1 }, 
    { "ai",         "application/postscript",           1 }, 
    { "aif",        "audio/x-aiff",                     1 }, 
    { "aifc",       "audio/x-aiff",                     1 }, 
    { "aiff",       "audio/x-aiff",                     1 }, 
    { "asc",        "text/plain",                       1 }, 
    { "atom",       "application/atom+xml",             1 }, 
    { "au",         "audio/basic",                      1 }, 
    { "avi",        "video/x-msvideo",                  1 }, 
    { "bcpio",      "application/x-bcpio",              1 }, 
    { "bin",        "application/octet-stream",         1 }, 
    { "bmp",        "image/bmp",                        1 }, 
    { "bz2",        "application/x-bzip2",              0 }, 
    { "cdf",        "application/x-netcdf",             1 }, 
    { "cgm",        "image/cgm",                        1 }, 
    { "class",      "application/octet-stream",         1 }, 
    { "cpio",       "application/x-cpio",               1 }, 
    { "cpt",        "application/mac-compactpro",       1 }, 
    { "csh",        "application/x-csh",                1 }, 
    { "css",        "text/css",                         1 }, 
    { "kl1",        "text/html",                        1 }, 
    { "klone",      "text/html",                        1 }, 
    { "dcr",        "application/x-director",           1 }, 
    { "dir",        "application/x-director",           1 }, 
    { "djv",        "image/vnd.djvu",                   1 }, 
    { "djvu",       "image/vnd.djvu",                   1 }, 
    { "dll",        "application/octet-stream",         1 }, 
    { "dmg",        "application/octet-stream",         1 }, 
    { "dms",        "application/octet-stream",         1 }, 
    { "doc",        "application/msword",               1 }, 
    { "dtd",        "application/xml-dtd",              1 }, 
    { "dvi",        "application/x-dvi",                1 }, 
    { "dxr",        "application/x-director",           1 }, 
    { "eps",        "application/postscript",           1 }, 
    { "etx",        "text/x-setext",                    1 }, 
    { "exe",        "application/octet-stream",         1 }, 
    { "ez",         "application/andrew-inset",         1 }, 
    { "gif",        "image/gif",                        0 }, 
    { "gram",       "application/srgs",                 1 }, 
    { "grxml",      "application/srgs+xml",             1 }, 
    { "gtar",       "application/x-gtar",               1 }, 
    { "gz",         "application/x-gzip",               0 }, 
    { "hdf",        "application/x-hdf",                1 }, 
    { "hqx",        "application/mac-binhex40",         0 }, 
    { "htm",        "text/html",                        1 }, 
    { "html",       "text/html",                        1 }, 
    { "ice",        "x-conference/x-cooltalk",          1 }, 
    { "ico",        "image/x-icon",                     1 }, 
    { "ics",        "text/calendar",                    1 }, 
    { "ief",        "image/ief",                        1 }, 
    { "ifb",        "text/calendar",                    1 }, 
    { "iges",       "model/iges",                       1 }, 
    { "igs",        "model/iges",                       1 }, 
    { "jpe",        "image/jpeg",                       0 }, 
    { "jpeg",       "image/jpeg",                       0 }, 
    { "jpg",        "image/jpeg",                       0 }, 
    { "json",       "application/json",                 1 },
    { "js",         "application/x-javascript",         1 }, 
    { "kar",        "audio/midi",                       1 }, 
    { "latex",      "application/x-latex",              1 }, 
    { "lha",        "application/octet-stream",         0 }, 
    { "lzh",        "application/octet-stream",         0 }, 
    { "m3u",        "audio/x-mpegurl",                  1 }, 
    { "m4u",        "video/vnd.mpegurl",                1 }, 
    { "man",        "application/x-troff-man",          1 }, 
    { "mathml",     "application/mathml+xml",           1 }, 
    { "me",         "application/x-troff-me",           1 }, 
    { "mesh",       "model/mesh",                       1 }, 
    { "mid",        "audio/midi",                       0 }, 
    { "midi",       "audio/midi",                       0 }, 
    { "mov",        "video/quicktime",                  0 }, 
    { "movie",      "video/x-sgi-movie",                0 }, 
    { "mp2",        "audio/mpeg",                       0 }, 
    { "mp3",        "audio/mpeg",                       0 }, 
    { "mpe",        "video/mpeg",                       0 }, 
    { "mpeg",       "video/mpeg",                       0 }, 
    { "mpg",        "video/mpeg",                       0 }, 
    { "mpga",       "audio/mpeg",                       0 }, 
    { "ms",         "application/x-troff-ms",           1 }, 
    { "msh",        "model/mesh",                       1 }, 
    { "mxu",        "video/vnd.mpegurl",                1 }, 
    { "nc",         "application/x-netcdf",             1 }, 
    { "oda",        "application/oda",                  1 }, 
    { "ogg",        "application/ogg",                  0 }, 
    { "pbm",        "image/x-portable-bitmap",          1 }, 
    { "pdb",        "chemical/x-pdb",                   1 }, 
    { "pdf",        "application/pdf",                  0 }, 
    { "pgm",        "image/x-portable-graymap",         1 }, 
    { "pgn",        "application/x-chess-pgn",          1 }, 
    { "png",        "image/png",                        0 }, 
    { "pnm",        "image/x-portable-anymap",          1 }, 
    { "ppm",        "image/x-portable-pixmap",          1 }, 
    { "ppt",        "application/vnd.ms-powerpoint",    1 }, 
    { "ps",         "application/postscript",           1 }, 
    { "qt",         "video/quicktime",                  0 }, 
    { "ra",         "audio/x-pn-realaudio",             0 }, 
    { "ram",        "audio/x-pn-realaudio",             0 }, 
    { "ras",        "image/x-cmu-raster",               1 }, 
    { "rdf",        "application/rdf+xml",              1 }, 
    { "rgb",        "image/x-rgb",                      1 }, 
    { "rm",         "application/vnd.rn-realmedia",     0 }, 
    { "roff",       "application/x-troff",              1 }, 
    { "rtf",        "text/rtf",                         1 }, 
    { "rtx",        "text/richtext",                    1 }, 
    { "sgm",        "text/sgml",                        1 }, 
    { "sgml",       "text/sgml",                        1 }, 
    { "sh",         "application/x-sh",                 1 }, 
    { "shar",       "application/x-shar",               1 }, 
    { "silo",       "model/mesh",                       1 }, 
    { "sit",        "application/x-stuffit",            1 }, 
    { "skd",        "application/x-koan",               1 }, 
    { "skm",        "application/x-koan",               1 }, 
    { "skp",        "application/x-koan",               1 }, 
    { "skt",        "application/x-koan",               1 }, 
    { "smi",        "application/smil",                 1 }, 
    { "smil",       "application/smil",                 1 }, 
    { "snd",        "audio/basic",                      1 }, 
    { "so",         "application/octet-stream",         1 }, 
    { "spl",        "application/x-futuresplash",       1 }, 
    { "src",        "application/x-wais-source",        1 }, 
    { "sv4cpio",    "application/x-sv4cpio",            1 }, 
    { "sv4crc",     "application/x-sv4crc",             1 }, 
    { "svg",        "image/svg+xml",                    1 }, 
    { "swf",        "application/x-shockwave-flash",    1 }, 
    { "t",          "application/x-troff",              1 }, 
    { "tar",        "application/x-tar",                1 }, 
    { "tcl",        "application/x-tcl",                1 }, 
    { "tex",        "application/x-tex",                1 }, 
    { "texi",       "application/x-texinfo",            1 }, 
    { "texinfo",    "application/x-texinfo",            1 }, 
    { "tif",        "image/tiff",                       1 }, 
    { "tiff",       "image/tiff",                       1 }, 
    { "tr",         "application/x-troff",              1 }, 
    { "tsv",        "text/tab-separated-values",        1 }, 
    { "txt",        "text/plain",                       1 }, 
    { "ustar",      "application/x-ustar",              1 }, 
    { "vcd",        "application/x-cdlink",             1 }, 
    { "vrml",       "model/vrml",                       1 }, 
    { "vxml",       "application/voicexml+xml",         1 }, 
    { "wav",        "audio/x-wav",                      1 }, 
    { "wbmp",       "image/vnd.wap.wbmp",               1 }, 
    { "wbxml",      "application/vnd.wap.wbxml",        1 }, 
    { "wml",        "text/vnd.wap.wml",                 1 }, 
    { "wmlc",       "application/vnd.wap.wmlc",         1 }, 
    { "wmls",       "text/vnd.wap.wmlscript",           1 }, 
    { "wmlsc",      "application/vnd.wap.wmlscriptc",   1 }, 
    { "wrl",        "model/vrml",                       1 }, 
    { "xbm",        "image/x-xbitmap",                  1 }, 
    { "xht",        "application/xhtml+xml",            1 }, 
    { "xhtml",      "application/xhtml+xml",            1 }, 
    { "xls",        "application/vnd.ms-excel",         1 }, 
    { "xml",        "application/xml",                  1 }, 
    { "xpm",        "image/x-xpixmap",                  1 }, 
    { "xsl",        "application/xml",                  1 }, 
    { "xslt",       "application/xslt+xml",             1 }, 
    { "xwd",        "image/x-xwindowdump",              1 }, 
    { "xyz",        "chemical/x-xyz",                   1 }, 
    { "zip",        "application/zip",                  0 },
#ifdef CUSTOM_MIME_ENTRIES
    CUSTOM_MIME_ENTRIES
#else
#endif
    { 0,            0,                                  0 }
};
