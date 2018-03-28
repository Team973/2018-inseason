
load("//tools/pathtool:pathtool_macros.bzl", "generate_headers")
load("//tools/pathtool:pathtool_macros.bzl", "visualize_paths")

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

visualize_paths(
    srcs = glob([
        "*.json",
    ]),
)
