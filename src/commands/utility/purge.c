#include "commands.h"

void purge_slash_command(struct discord *client, const struct discord_interaction *event)
{
    u64snowflake ch_id = event->channel_id;
    struct discord_application_command_interaction_data_options *amount_option =
        event->data->options;
    char *amount = amount_option->array[0].value;

    struct discord_get_channel_messages params = {.limit = atoi(amount)};

    struct discord_ret_messages ret = {
        .keep = event,
        .done = &on_purge_read_success};

    discord_get_channel_messages(client, ch_id, &params, &ret);

    struct discord_interaction_response params_response = {
        .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
        .data = &(struct discord_interaction_callback_data){
            .content = "purging messages..."}};
    discord_create_interaction_response(client, event->id,
                                        event->token, &params_response, NULL);
}

//////////////////////////////////////////////////////////////////////////////////////

void purge_message_command(struct discord *client, const struct discord_message *event)
{
    u64snowflake ch_id = event->channel_id;
    char *amount = event->content;
    if (!amount)
        return; // No amount specified
    int amount_int = atoi(amount) + 1;
    if (amount_int > 100 || amount_int <= 1)
        return; // Invalid amount

    struct discord_get_channel_messages params = {.limit = amount_int};

    struct discord_ret_messages ret = {
        .keep = event,
        .done = &M_on_purge_read_success};

    discord_get_channel_messages(client, ch_id, &params, &ret);
}