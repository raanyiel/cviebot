#include "commands.h"

void best_slash_command(struct discord *client, const struct discord_interaction *event)
{
    discord_create_interaction_response(client, event->id, event->token,
                                        &(struct discord_interaction_response){
                                            .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
                                            .data = &(struct discord_interaction_callback_data){
                                                .content = "fetching best girl...",
                                            },
                                        },
                                        NULL);

    process_best_girl_output(client, 0, 0, true, event->application_id, event->token);
}

void best_message_command(struct discord *client, const struct discord_message *event)
{
    discord_create_message(client, event->channel_id,
                           &(struct discord_create_message){
                               .content = "fetching best girl...",
                           },
                           &(struct discord_ret_message){
                               .done = best_message_callback});
}
