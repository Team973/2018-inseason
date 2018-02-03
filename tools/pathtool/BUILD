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
    name = "generatePath",
    srcs = [
          "generatePath.py",
    ],
    deps = [
         ":pypathfinder",
    ],
)

genrule(
    name = "generate_path_header",
    outs = [
        "trajectory.h",
    ],
    tools = [
        ":generatePath",
        ":pypathfinder",
        "//third_party/pathfinder:pathfinder_cdll.so",
    ],
    srcs = [
        "sampleJSON",
    ],
    cmd = "$(location :generatePath) $(location sampleJSON) $@",
)
