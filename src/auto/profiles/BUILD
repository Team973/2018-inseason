
load("//tools/pathtool:pathtool_macros.bzl", "generate_headers")

generate_headers(
    srcs = glob([
        "*.json",
    ]),
    tools = [
        "//tools/pathtool:path_generator",
        "//third_party/pathfinder:pathfinder_cdll.so",
    ],
    cmd = "$(location //tools/pathtool:path_generator) $(location #SOURCE_FILE#) $@ $(location //third_party/pathfinder:pathfinder_cdll.so)",
)
