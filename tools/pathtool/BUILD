
py_library(
    name = "pypathfinder",
    srcs = [
        "pypathfinder.py",
    ],
    data = [
        "//third_party/pathfinder:pathfinder_cdll.so",
    ],
)

py_test(
    name = "test",
    srcs = [
        "test.py",
    ],
    deps = [
        ":pypathfinder",
    ],
)

py_binary(
    name = "path_generator",
    srcs = [
        "path_generator.py",
    ],
    deps = [
        ":pypathfinder",
    ],
    visibility = ["//visibility:public"],
)

genrule(
    name = "generate_path_header",
    outs = [
        "trajectory.h",
    ],
    tools = [
        ":path_generator",
        "//third_party/pathfinder:pathfinder_cdll.so",
    ],
    srcs = [
        "sample.json",
    ],
    cmd = "$(location :path_generator) $(location sample.json) $@ $(location //third_party/pathfinder:pathfinder_cdll.so)",
    visibility = ["//visibility:public"],
)
