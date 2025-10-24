#include "commands.h"

void on_purge_success(struct discord *client, struct discord_response *resp)
{
    struct discord_interaction *event = (struct discord_interaction *)resp->keep;
    discord_edit_original_interaction_response(client, event->application_id,
                                               event->token,
                                               &(struct discord_edit_original_interaction_response){
                                                   .content = "messages purged :3"},
                                               NULL);
}

void M_on_purge_success(struct discord *client, struct discord_response *resp)
{
    struct discord_message *event = (struct discord_message *)resp->keep;
    struct discord_create_message params = {.content = "messages purged :3"};
    discord_create_message(client, event->channel_id, &params, NULL);
}

void on_purge_read_success(struct discord *client, struct discord_response *resp, const struct discord_messages *msgs)
{
    struct discord_interaction *event = (struct discord_interaction *)resp->keep;
    size_t msg_count = msgs->size;
    struct snowflakes msg_ids = {.size = msg_count, .array = malloc(sizeof(u64snowflake) * msg_count)};
    for (size_t i = 0; i < msg_count; ++i)
    {
        msg_ids.array[i] = msgs->array[i].id;
    }

    struct discord_ret ret = {
        .keep = event,
        .done = &on_purge_success,
    };

    struct discord_bulk_delete_messages params = {
        .messages = &msg_ids,
    };

    if (msg_count > 1)
    {
        discord_bulk_delete_messages(client, event->channel_id, &params, &ret);
    }
    else
    {
        discord_delete_message(client, event->channel_id, msg_ids.array[0], NULL, &ret);
    }
    free(msg_ids.array);
}

void M_on_purge_read_success(struct discord *client, struct discord_response *resp, const struct discord_messages *msgs)
{
    struct discord_message *event = (struct discord_message *)resp->keep;
    size_t msg_count = msgs->size;
    struct snowflakes msg_ids = {.size = msg_count, .array = malloc(sizeof(u64snowflake) * msg_count)};
    for (size_t i = 0; i < msg_count; ++i)
    {
        msg_ids.array[i] = msgs->array[i].id;
    }

    struct discord_ret ret = {
        .keep = event,
        .done = &M_on_purge_success,
    };

    struct discord_bulk_delete_messages params = {
        .messages = &msg_ids,
    };

    discord_bulk_delete_messages(client, event->channel_id, &params, &ret);
    free(msg_ids.array);
}
