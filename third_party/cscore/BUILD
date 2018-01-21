licenses(["permissive"])

cc_library(
    name = "cscore",
    srcs = glob([
        "src/main/native/cpp/**/*.cpp",
        "src/main/native/cpp/**/*.hpp",
        "src/main/native/cpp/**/*.h",
    ],
    exclude = glob(["src/main/native/cpp/jni/*.cpp"]),
    ),
    hdrs = glob([
        "src/main/native/include/*.h",
        "src/main/native/include/*.inl",
        "src/main/native/cpp/*.inl",
    ]),
    includes = [
        "src/main/native/include",
    ],
    deps = [
        "//third_party/wpiutil:wpiutil",
        "//third_party/opencv:opencv",
    ],
    visibility = ["//visibility:public"],
)
