
filegroup(
    name = "robotCommand",
    srcs = [
        "data/robotCommand",
    ],
)

sh_binary(
    name = "deploy",
    srcs = ["deploy.sh"],
    data = [
        "//src:robot",
        ":robotCommand",
        "//third_party/opencv:opencv_libs",
    ],
    args = [
        "$(location //src:robot)",
        "$(location :robotCommand)",
        "$(locations //third_party/opencv:opencv_libs)",
    ],
)

sh_binary(
    name = "generate-docs",
    srcs = ["//tools/doxygen:doxygen_build"],
    data = [
        "//tools/doxygen:doxyfile",
        "//src:robot_src",
    ],
    args = ["$(location //src:robot_src)"],
)
