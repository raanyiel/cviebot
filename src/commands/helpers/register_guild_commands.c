#include "commands.h"

void register_guild_commands(struct discord *client, const struct discord_ready *event)
{
    u64snowflake GUILD_ID = (u64snowflake)getenv("GUILD_ID");
    if (!GUILD_ID)
    {
        fprintf(stderr, "Please set the GUILD_ID environment variable. This will be changed in the future to automatically register in all guilds.\n");
        exit(EXIT_FAILURE);
    }
    discord_create_guild_application_command(client, event->application->id,
                                             GUILD_ID, &ping_params, NULL);

    discord_create_guild_application_command(client, event->application->id,
                                             GUILD_ID, &purge_params, NULL);
}
