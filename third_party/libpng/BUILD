licenses(["permissive"])

genrule(
    name = "conf",
    srcs = [
        "scripts/pnglibconf.h.prebuilt",
    ],
    outs = ["pnglibconf.h"],
    cmd = "cat $(location scripts/pnglibconf.h.prebuilt) > $@",
    message = "generating configuration file",
)

cc_library(
    name = "pnglibconf",
    hdrs = [":conf"],
    strip_include_prefix = "//third_party/libpng",
)

cc_library(
    name = "libpng",
    srcs = glob([
        "*.c",
    ]),
    hdrs = glob([
        "*.h",
    ]),
    strip_include_prefix = "//third_party/libpng",
    deps = [
        ":pnglibconf",
        "//third_party/zlib:zlib",
    ],
    visibility = ["//visibility:public"],
)
