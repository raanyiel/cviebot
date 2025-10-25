#include "commands.h"
#include <concord/log.h>

void process_best_girl_output(struct discord *client, u64snowflake channel_id, u64snowflake message_id, bool is_slash, u64snowflake application_id, char *token)
{
    FILE *fp;
    char buffer[1024];
    char *command = "python src/scripts/best.py";

    fp = popen(command, "r");
    if (fp == NULL)
    {
        perror("Failed to run command");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (strncmp(buffer, "Error", 5) == 0)
        {
            log_error("%s", buffer);
            if (is_slash)
            {
                discord_edit_original_interaction_response(client, application_id, token,
                                                           &(struct discord_edit_original_interaction_response){
                                                               .content = "an error occurred while fetching best girl :(",
                                                           },
                                                           NULL);
            }
            else
            {
                discord_edit_message(client, channel_id, message_id,
                                     &(struct discord_edit_message){
                                         .content = "an error occurred while fetching best girl :(",
                                     },
                                     NULL);
            }
            break;
        }

        if (is_slash)
        {
            discord_edit_original_interaction_response(client, application_id, token,
                                                       &(struct discord_edit_original_interaction_response){
                                                           .content = buffer,
                                                       },
                                                       NULL);
        }
        else
        {
            discord_edit_message(client, channel_id, message_id,
                                 &(struct discord_edit_message){
                                     .content = buffer,
                                 },
                                 NULL);
        }
    }

    pclose(fp);
}

void best_message_callback(struct discord *client, struct discord_response *resp, const struct discord_message *ret)
{
    process_best_girl_output(client, ret->channel_id, ret->id, false, 0, NULL);
}