licenses(["permissive"])

cc_library(
    name = "wpiutil",
    srcs = glob([
        "src/main/native/cpp/**/*.cpp",
        "src/main/native/cpp/llvm/Unix/Path.inc",
        "src/main/native/cpp/**/*.h",
    ]),
    hdrs = glob([
        "src/main/native/include/**/*.h",
        "src/main/native/include/**/*.inl",
    ]),
    includes = [
        "src/main/native/include",
    ],
    visibility = ["//visibility:public"],
)
