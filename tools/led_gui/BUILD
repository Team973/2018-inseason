cc_binary(
  name = "led_gui",
  srcs = ["led_gui.cpp"],
  deps = [
    "//lib/helpers:greylight",
    "//lib/pixelprocessors:pixelprocessors"
  ],
  linkopts = [
    "-L/usr/local/lib",
    "-lsfml-graphics",
    "-lsfml-window",
    "-lsfml-system",
    "-lpthread",
    "-lm"
  ],
)
