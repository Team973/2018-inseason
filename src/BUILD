filegroup(
    name = "src",
    srcs = ["."],
    visibility = ["//visibility:public"],
)

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
        "//lib/trajectories:trajectories",
        "//src/auto:auto",
        "//lib/sensors:sensors",
        "//src/controllers:controllers",
        "//src/info:info",
        "//src/subsystems:subsystems",
    ],
    visibility = ["//visibility:public"],
)
