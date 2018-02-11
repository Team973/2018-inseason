
cc_library(
    name = "auto",
    srcs = glob([
        "*.cpp",
    ]),
    hdrs = glob([
        "*.h",
    ]) + [
        "//tools/pathtool:generate_path_header",
    ],
    deps = [
        "//third_party/wpilibsuite:wpilib",
        "//third_party/ctre:ctre",
        "//lib/trajectories:trajectories",
    ],
    visibility = ["//visibility:public"],
)
