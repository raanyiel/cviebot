#ifndef HELPERS_H
#define HELPERS_H
extern void on_purge_success(struct discord *client, struct discord_response *resp);
extern void M_on_purge_success(struct discord *client, struct discord_response *resp);
extern void on_purge_read_success(struct discord *client, struct discord_response *resp, const struct discord_messages *msgs);
extern void M_on_purge_read_success(struct discord *client, struct discord_response *resp, const struct discord_messages *msgs);

extern void process_best_girl_output(struct discord *client, u64snowflake channel_id, u64snowflake message_id, bool is_slash, u64snowflake application_id, char *token);
extern void best_message_callback(struct discord *client, struct discord_response *resp, const struct discord_message *ret);

extern void register_guild_commands(struct discord *client, const struct discord_ready *event);
extern void register_message_commands(struct discord *client);

#endif // HELPERS_H