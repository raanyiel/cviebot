#include "commands.h"

struct discord_create_guild_application_command ping_params = {
    .name = "ping",
    .description = "Ping away to your heart's content!"};

struct discord_create_guild_application_command purge_params = {
    .name = "purge",
    .description = "Purge a number of messages from the channel.",
    .options = &purge_options};