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
