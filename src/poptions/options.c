#include "commands.h"

struct discord_application_command_option purge_option[] =
    {
        {
            .type = DISCORD_APPLICATION_OPTION_INTEGER,
            .name = "amount",
            .description = "Number of messages to purge (max 100)",
            .required = true,
            .max_value = "100",
            .min_value = "1",
        },
};

struct discord_application_command_options purge_options =
    {
        .size = sizeof(purge_option) / sizeof(*purge_option),
        .array = purge_option};