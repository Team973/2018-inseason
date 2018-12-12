
cc_library(
    name = "controllers",
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
        "//lib/bases:bases",
        "//lib/helpers:helpers",
        "//lib/profiles:profiles",
        "//lib/util:util",
        "//lib/sensors:sensors",
        "//lib/trajectories:trajectories",
        "//src/info:info",
    ],
    visibility = ["//visibility:public"],
)
