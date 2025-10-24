#include "commands.h"
#include <concord/log.h>
#include <stdio.h>

void on_ready(struct discord *client, const struct discord_ready *event)
{
    register_guild_commands(client, event);
    log_info("Logged in as %s!", event->user->username);
}

int main(void)
{
    char *BOT_TOKEN = getenv("DISCORD_TOKEN");
    if (!BOT_TOKEN)
    {
        fprintf(stderr, "Please set the DISCORD_TOKEN environment variable.\n");
        return EXIT_FAILURE;
    }
    struct discord *client = discord_init(BOT_TOKEN);
    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);
    discord_set_prefix(client, ".");
    discord_set_on_ready(client, &on_ready);
    discord_set_on_interaction_create(client, &slash_command_handler);
    register_message_commands(client);
    discord_run(client);
}