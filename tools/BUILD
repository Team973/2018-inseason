
load(":deploy_macros.bzl", "add_team_numbers", "get_team_number_options")

# List all team numbers that you will deploy to here
# The first number listed will be used as the default number
team_numbers = ["973", "8973", "9973"]

add_team_numbers(numbers = team_numbers)

filegroup(
    name = "robotCommand",
    srcs = [
        "data/robotCommand",
    ],
)

sh_binary(
    name = "deploy",
    srcs = ["deploy.sh"],
    data = [
        "//src:robot",
        ":robotCommand",
        "//third_party/opencv:opencv_libs",
    ],
    #args = select(get_team_number_options(
    #        args = [
    #            "TEAM_NUMBER_HERE",
    #            "$(location //src:robot)",
    #            "$(location :robotCommand)",
    #            "$(locations //third_party/opencv:opencv_libs)",
    #        ],
    #        numbers = team_numbers,
    #        number_location = 0,
    #        )),
    args = [
        "$(location //src:robot)",
        "$(location :robotCommand)",
        "$(locations //third_party/opencv:opencv_libs)",
        ],
)
