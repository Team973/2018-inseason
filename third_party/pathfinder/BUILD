licenses(["permissive"])

cc_library(
    name = "pathfinder",
    srcs = glob([
        "Pathfinder-Core/src/**/*.c",
    ]),
    hdrs = glob([
        "Pathfinder-Core/include/**/*.h"
    ]),
    includes = [
        "Pathfinder-Core/include"
    ],
    visibility = ["//visibility:public"],
)

# Pathfinder library in a form that can be imported by py ctypes
cc_binary(
    name = "pathfinder_cdll.so",
    srcs = glob([
        "Pathfinder-Core/src/**/*.c",
        "Pathfinder-Core/include/**/*.h",
    ]),
    includes = [
        "Pathfinder-Core/include"
    ],
    copts = [
        "-fPIC",
        "-Wno-unused-variable",
        "-Wno-missing-field-initializers",
    ],
    linkstatic = 1,
    linkshared = 1,
    visibility = ["//visibility:public"],
)
