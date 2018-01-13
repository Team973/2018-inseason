
cc_library(
    name = "subsystems",
    srcs = glob([
        "*.cpp",
    ]),
    hdrs = glob([
        "*.h",
    ]),
    deps = [
        "//third_party/wpilibsuite:wpilib",
        "//third_party/ctre:ctre",
        "//lib/managers:managers",
        "//lib/logging:logging",
        "//src/controllers:controllers",
        "//src/info:info",
    ],
    visibility = ["//visibility:public"],
)
