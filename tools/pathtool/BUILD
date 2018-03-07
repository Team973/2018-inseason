
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

py_library(
    name = "libvisualize",
    srcs = [
        "libvisualize.py",
    ],
    deps = [
        ":pypathfinder",
    ],
    visibility = ["//visibility:public"],
)
