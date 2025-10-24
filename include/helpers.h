#ifndef HELPERS_H
#define HELPERS_H
extern void on_purge_success(struct discord *client, struct discord_response *resp);
extern void M_on_purge_success(struct discord *client, struct discord_response *resp);
extern void on_purge_read_success(struct discord *client, struct discord_response *resp, const struct discord_messages *msgs);
extern void M_on_purge_read_success(struct discord *client, struct discord_response *resp, const struct discord_messages *msgs);

extern void register_guild_commands(struct discord *client, const struct discord_ready *event);
extern void register_message_commands(struct discord *client);

#endif // HELPERS_H