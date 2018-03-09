
cc_library(
    name = "helpers",
    srcs = glob([
        "*.cpp",
    ]),
    hdrs = glob([
        "*.h",
    ]),
    deps = [
        "//third_party/wpilibsuite:wpilib",
        "//third_party/ctre:ctre",
        "//lib/filters:filters",
        "//lib/util:util",
        "//lib/managers:managers",
        "//lib/logging:logging",
        ":greylight",
        ":apa102"
    ],
    visibility = ["//visibility:public"],
)
cc_library(
    name = "apa102",
    srcs = glob([
        "APA102.cpp",
    ]),
    hdrs = glob([
        "APA102.h",
    ]),
    deps = [
        "//third_party/wpilibsuite:wpilib",
        "//lib/pixelprocessors:pixelprocessors",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "greylight",
    srcs = glob([
        "GreyLight.cpp",
    ]),
    hdrs = glob([
        "GreyLight.h",
    ]),
    defines = select({
        ":using_led_simulator": ["USING_LED_SIMULATOR"],
        "//conditions:default": [],
    }),
    deps = select({
        ":using_led_simulator": ["//lib/pixelprocessors:pixelprocessors"],
        "//conditions:default": [
            "//lib/pixelprocessors:pixelprocessors",
            ":apa102"
        ],
    }),
    visibility = ["//visibility:public"],
)
config_setting(
    name = "using_led_simulator",
    values = {
      "define": "simulate=true",
    }
)
