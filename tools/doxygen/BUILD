genrule(
    name = "generate-docs",
    srcs = [
        ":doxygen.sh",
        ":Doxyfile.in",
        "//docs:docs",
        "//lib:lib",
        "//src:src",
        "//third_party:third_party",
        "//:readme",
    ],
    outs = ["docs.zip"],
    cmd = "sh $(location :doxygen.sh) $(location docs.zip)",
)

genrule(
    name = "generate-short-docs",
    srcs = [
        ":doxygen.sh",
        ":Doxyfile.in",
        "//docs:docs",
        "//lib:lib",
        "//src:src",
        "//:readme",
    ],
    outs = ["shortdocs.zip"],
    cmd = "sh $(location :doxygen.sh) short $(location shortdocs.zip)",
)
