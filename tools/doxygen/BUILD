filegroup(
    name = "doxygen_build",
    srcs = ["doxygen.sh"],
    visibility = ["//visibility:public"],
)

filegroup(
  name = "doxyfile",
  srcs = ["Doxyfile.in"],
  visibility = ["//visibility:public"],
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
