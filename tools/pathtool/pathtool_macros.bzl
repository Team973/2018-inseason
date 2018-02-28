
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
