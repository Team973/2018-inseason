licenses(["permissive"])

cc_library(
    name = "ntcore",
    srcs = glob([
        "src/main/native/cpp/**/*.cpp",
        "src/main/native/cpp/**/*.h",
    ],
    exclude = [
        "src/main/native/cpp/jni/NetworkTablesJNI.cpp",
    ]),
    hdrs = glob([
        "src/main/native/include/**/*.h",
        "src/main/native/include/**/*.inl",
    ]),
    includes = [
        "src/main/native/include",
    ],
    deps = [
        "//third_party/wpiutil:wpiutil",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)
