#include <concord/discord.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"
#include "handlers.h"
#include "options.h"
#include "params.h"
#ifndef COMMANDS_H
#define COMMANDS_H

extern void ping_slash_command(struct discord *client, const struct discord_interaction *event);
extern void ping_message_command(struct discord *client, const struct discord_message *event);

extern void purge_slash_command(struct discord *client, const struct discord_interaction *event);
extern void purge_message_command(struct discord *client, const struct discord_message *event);

//////////////////////////////////////////////////////////////////////////////////////

#endif // COMMANDS_H