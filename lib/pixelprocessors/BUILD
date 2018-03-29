
cc_library(
    name = "pixelprocessors",
    srcs = glob([
        "*.cpp",
    ]),
    hdrs = glob([
        "*.h",
    ]),
    defines = select({
        ":using_led_simulator": ["USING_LED_SIMULATOR"],
        "//conditions:default": [],
    }),
    deps = select({
        ":using_led_simulator": [],
        "//conditions:default": [
            "//lib/util:util"
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
