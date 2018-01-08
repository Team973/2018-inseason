licenses(["permissive"])

cc_library(
    name = "ctre",
    srcs = glob([
        "cpp/lib/*.a",
    ]),
    hdrs = glob([
        "cpp/include/**/*.h",
    ]),
    includes = [
        "cpp/include",
        "cpp/include/ctre",
    ],
    deps = [
        "//third_party/wpilibsuite:wpilib",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)
