
cc_binary(
    name = "robot",
    srcs = glob([
        "*.cpp",
        "*.h",

    ]),
    copts = [
        "-lpthread",
    ],
    deps = [
        "//third_party/wpilibsuite:wpilib",
        "//third_party/ctre:ctre",
        "//lib/helpers:helpers",
        "//src/auto:auto",
        "//src/subsystems:subsystems",
        "//src/info:info",
    ],
    visibility = ["//visibility:public"],
)
