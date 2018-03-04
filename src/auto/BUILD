
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
        "//src/auto/profiles:sample_header",
        "//src/auto/profiles:centerleftswitch_header",
        "//src/auto/profiles:centerrightswitch_header",
        "//src/auto/profiles:leftscale_header",
        "//src/auto/profiles:rightscale_header",
        "//src/auto/profiles:leftscaleopposite_header",
        "//src/auto/profiles:rightscaleopposite_header",
        "//src/auto/profiles:rightswitchopposite_header",
        "//src/auto/profiles:leftswitchopposite_header",
        "//src/auto/profiles:leftsideswitch_header",
        "//src/auto/profiles:rightsideswitch_header",
        "//src/auto/profiles:righttwocube_header",
        "//src/auto/profiles:lefttwocube_header",
    ],
    visibility = ["//visibility:public"],
)
