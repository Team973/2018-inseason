
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
