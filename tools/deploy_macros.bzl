
def add_team_numbers(numbers):
    for n in numbers:
        native.config_setting(
                name = "generated-" + n,
                values = {
                    "define": "team=" + n,
                    },
                )

def get_team_number_options(args, numbers, number_location):
    num_dict = {}
    for n in list(numbers):
        new_args = [v for k,v in enumerate(args) if k != number_location]
        new_args.insert(number_location, n)
        if not "//conditions:default" in num_dict:
            num_dict["//conditions:default"] = new_args

        num_dict[":generated-" + n] = new_args

    return num_dict
