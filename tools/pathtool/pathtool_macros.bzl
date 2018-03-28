
def generate_headers(srcs, tools, cmd):
    for s in srcs:
        tName = s.rstrip(".json")
        tmpCmd = cmd
        tmpCmd = tmpCmd.replace("#SOURCE_FILE#", s)
        native.genrule(
            name = "generate_{}_header".format(tName),
            outs = [
                "{}_trajectory.h".format(tName),
            ],
            tools = tools,
            srcs = [
                s,
            ],
            cmd = tmpCmd,
        )
        native.cc_library(
            name = "{}_header".format(tName),
            srcs = [],
            hdrs = [":generate_{}_header".format(tName)],
            visibility = ["//visibility:public"],
        )

def visualize_paths(srcs):
    for s in srcs:
        tName = s.rstrip(".json")
        native.py_binary(
            name = "visualize_{}".format(tName),
            srcs = [
                "visualize.py",
            ],
            main = "visualize.py",
            deps = [
                "//tools/pathtool:libvisualize",
            ],
            data = [
                s,
                "//third_party/pathfinder:pathfinder_cdll.so",
            ],
            args = [
                "$(location {})".format(s),
                "$(location //third_party/pathfinder:pathfinder_cdll.so)",
            ],
            visibility = ["//visibility:public"],
        )
