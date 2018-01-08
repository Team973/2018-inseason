licenses(["permissive"])

genrule(
    name = "conf",
    outs = ["jconfig.h"],
    cmd = "echo -e \"" + "\n".join([
    "// This is a generated file DO NOT EDIT",
    "#define HAVE_PROTOTYPES",
    "#define HAVE_UNSIGNED_CHAR",
    "#define HAVE_UNSIGNED_SHORT",
    "#undef CHAR_IS_UNSIGNED",
    "#define HAVE_STDDEF_H",
    "#define HAVE_STDLIB_H",
    "#undef NEED_BSD_STRINGS",
    "#undef NEED_SYS_TYPES_H",
    "#undef NEED_FAR_POINTERS",
    "#undef NEED_SHORT_EXTERNAL_NAMES",
    "#undef INCOMPLETE_TYPES_BROKEN",
    "#ifdef JPEG_INTERNALS",
    "#undef RIGHT_SHIFT_IS_UNSIGNED",
    "#endif /* JPEG_INTERNALS */",
    "#ifdef JPEG_CJPEG_DJPEG",
    "#define BMP_SUPPORTED		/* BMP image file format */",
    "#define GIF_SUPPORTED		/* GIF image file format */",
    "#define PPM_SUPPORTED		/* PBMPLUS PPM/PGM image file format */",
    "#undef RLE_SUPPORTED		/* Utah RLE image file format */",
    "#define TARGA_SUPPORTED		/* Targa image file format */",
    "#undef NEED_SIGNAL_CATCHER",
    "#undef DONT_USE_B_MODE",
    "#undef PROGRESS_REPORT",
    "#endif /* JPEG_CJPEG_DJPEG */",
    ]) + "\" > $@",
    message = "generating configuration file",
)

cc_library(
    name = "jconfig",
    hdrs = [":conf"],
    strip_include_prefix = "//third_party/libjpeg",
)

cc_library(
    name = "libjpeg",
    srcs = glob([
        "*.c",
    ],
    exclude = [
        "ansi2knr.c",
        "jmemmac.c",
        "jmemdos.c",
        "jmemname.c",
        "jmemnobs.c",
        "example.c",
        "cjpeg.c",
        "djpeg.c",
        "jpegtran.c",
        "rdjpgcom.c",
        "wrjpgcom.c",
    ],
    ),
    hdrs = glob([
        "*.h",
    ],
    exclude = [
    ],
    ),
    strip_include_prefix = "//third_party/libjpeg",
    deps = [
        ":jconfig",
    ],
    copts = [
        "-Wno-main",
    ],
    visibility = ["//visibility:public"],
)
