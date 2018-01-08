licenses(["permissive"])

cc_library(
    name = "opencv",
    srcs = glob([
        "opencv/lib/static/*.a",
        "opencv/lib/shared/*.so.3.2",
    ]),
    hdrs = glob([
        "opencv/include/opencv2/**/*.h",
        "opencv/include/opencv2/**/*.hpp",
    ]),
    includes = [
        "opencv/include",
    ],
)

cc_library(
    name = "cscore",
    srcs = glob([
        "src/*.cpp",
        "src/*.hpp",
        "src/*.h",
    ]),
    hdrs = glob([
        "include/*.h",
        "include/*.inl",
        "src/*.inl",
    ]),
    includes = [
        "include",
    ],
    deps = [
        "//third_party/ntcore:wpiutil",
        ":opencv",
    ],
    visibility = ["//visibility:public"],
)
