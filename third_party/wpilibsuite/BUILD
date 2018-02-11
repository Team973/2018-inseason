licenses(["permissive"])

cc_library(
    name = "hal",
    srcs = glob([
        "hal/src/main/native/athena/**/*.cpp",
        "hal/src/main/native/athena/**/*.h",
        "hal/src/main/native/shared/**/*.cpp",
    ]),
    hdrs = glob([
        "hal/src/main/native/include/HAL/**/*.h",
    ],
    exclude = [
        "hal/src/main/native/include/HAL/LabVIEW/HAL.h",
    ]),
    includes = [
        "hal/src/main/native/include",
    ],
    copts = [
        "-Wno-deprecated-declarations", # wpilib uses deprecated functions
    ],
    linkopts = [
        "-lpthread",
        "-lm",
    ],
    deps = [
        ":ni-libraries",
        "//third_party/ntcore:ntcore",
        "//third_party/wpiutil:wpiutil",
    ],
)

filegroup(
    name = "ni-lib-files",
    srcs = [ "ni-libraries/lib/%s" % s for s in [
        "libFRC_NetworkCommunication.so.18.0.0",
        "libNiFpga.so.17.0.0",
        "libNiFpgaLv.so.17.0.0",
        "libniriodevenum.so.17.0.0",
        "libniriosession.so.17.0.0",
        "libNiRioSrv.so.17.0.0",
        "libRoboRIO_FRC_ChipObject.so.18.0.0",
        "libvisa.so",
    ]],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "ni-libraries",
    srcs = [ "ni-lib-files" ],
    hdrs = glob([
        "ni-libraries/include/**/*.h",
    ]),
    includes = [
        "ni-libraries/include",
    ],
    linkstatic = 1,
    copts = [
        "-Wno-deprecated-declarations", # wpilib uses deprecated functions
    ],
)

genrule(
    name = "version",
    outs = ["WPILibVersion.cpp"],
    cmd = 'echo -e "// This is a generated file\n// Please do not edit\n#include \\"WPILibVersion.h\\"\n\nconst char* GetWPILibVersion() {\n return \\"frc973\\";\n }" > $@',
)

cc_library(
    name = "WPILibVersion",
    srcs = [":version"],
    hdrs = ["wpilibc/src/main/native/include/WPILibVersion.h"],
    strip_include_prefix = "wpilibc/src/main/native/include",
)

cc_library(
    name = "wpilib",
    srcs = glob([
            "wpilibc/src/main/native/cpp/**/*.cpp",
    ]),
    hdrs = glob([
        "wpilibc/src/main/native/include/**/*.h",
        "wpilibc/src/main/native/include/**/*.inc",
    ],
    exclude = [
        "wpilibc/src/main/native/include/WPILibVersion.h",
        ],
    ),
    copts = [
        "-Wno-deprecated-declarations", # wpilib uses deprecated functions
    ],
    linkopts = [
        "-lpthread",
        "-ldl",
        "-lm",
    ],
    includes = [
        "wpilibc/src/main/native/include",
    ],
    deps = [
        ":hal",
        ":ni-libraries",
        ":WPILibVersion",
        "//third_party/ntcore:ntcore",
        "//third_party/wpiutil:wpiutil",
        "//third_party/cscore:cscore",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)
