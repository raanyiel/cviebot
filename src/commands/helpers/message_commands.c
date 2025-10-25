#include "commands.h"

void register_message_commands(struct discord *client)
{
    discord_set_on_command(client, "ping", &ping_message_command);
    discord_set_on_command(client, "purge", &purge_message_command);
    discord_set_on_command(client, "best", &best_message_command);
}