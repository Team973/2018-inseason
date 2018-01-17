
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
        "//third_party/ctre:ctre",
        "//third_party/wpilibsuite:wpilib",
        "//lib/helpers:helpers",
        "//src/auto:auto",
        "//src/subsystems:subsystems",
        "//src/info:info",
    ],
    visibility = ["//visibility:public"],
)
