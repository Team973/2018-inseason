
cc_library(
    name = "helpers",
    srcs = glob([
        "*.cpp",
    ]),
    hdrs = glob([
        "*.h",
    ]),
    deps = [
        "//third_party/wpilibsuite:wpilib",
        "//third_party/ctre:ctre",
        "//lib/filters:filters",
        "//lib/util:util",
        "//lib/managers:managers",
        "//lib/logging:logging",
        ":greylight"
    ],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "greylight",
    srcs = glob([
        "GreyLight.cpp",
    ]),
    hdrs = glob([
        "GreyLight.h",
    ]),
    deps = [
        "//lib/pixelprocessors:pixelprocessors"
    ],
    visibility = ["//visibility:public"],
)
