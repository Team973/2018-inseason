
cc_library(
    name = "auto",
    srcs = glob([
        "*.cpp",
    ]),
    hdrs = glob([
        "*.h",
    ]),
    deps = [
        "//third_party/wpilibsuite:wpilib",
        "//third_party/ctre:ctre",
        "//lib/trajectories:trajectories",
        "//src/subsystems:subsystems",
        "//src/auto/profiles:leftswitch_header",
        "//src/auto/profiles:rightswitch_header",
        "//src/auto/profiles:leftscale_header",
        "//src/auto/profiles:rightscale_header",
    ],
    visibility = ["//visibility:public"],
)
