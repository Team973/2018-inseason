licenses(["permissive"])

filegroup(
    name = "opencv_libs",
    srcs = glob([
        "*.so.*",
        "*.so",
    ]),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "opencv",
    srcs = [":opencv_libs"],
    #srcs = glob([
    #    "*.so.*",
    #    "*.so",
    #]),
    hdrs = glob([
        "include/opencv2/**/*.h",
        "include/opencv2/**/*.hpp",
    ]),
    includes = [
        "include",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)
