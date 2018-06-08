
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
        "//docs:docs",
        "//lib:lib_files",
        "//src:src_files",
        "//third_party:thirdparty_files",
        "//:readme",
    ],
)

sh_binary(
    name = "generate-short-docs",
    srcs = ["//tools/doxygen:doxygen_build"],
    data = [
        "//tools/doxygen:doxyfile",
        "//docs:docs",
        "//lib:lib_files",
        "//src:src_files",
        "//third_party:thirdparty_files",
        "//:readme",
    ],
    args = ["short"],
)

sh_binary(
    name = "open-docs",
    srcs = ["//tools/doxygen:doxygen_build"],
    data = [
        "//tools/doxygen:doxyfile",
        "//docs:docs",
        "//lib:lib_files",
        "//src:src_files",
        "//third_party:thirdparty_files",
        "//:readme",
    ],
    args = ["open"],
)
