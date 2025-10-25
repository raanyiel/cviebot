#include "commands.h"

void slash_command_handler(struct discord *client, const struct discord_interaction *event)
{
    if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND)
        return; /* return if interaction isn't a slash command */

    if (strcmp(event->data->name, "ping") == 0)
    {
        ping_slash_command(client, event);
    }
    else if (strcmp(event->data->name, "purge") == 0)
    {
        purge_slash_command(client, event);
    }
    else if (strcmp(event->data->name, "best") == 0)
    {
        best_slash_command(client, event);
    }
}
