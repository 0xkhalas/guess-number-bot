#include <stdio.h>
#include <string.h>
#include <concord/discord.h>
#include "commands.h"

#define BOT_TOKEN "MTE2NTY3ODIzMjM3NzQ5OTczOQ.G64pC8._X358LT6z-LVmQkdpZsa1zao9HopGXKXVh7DbM"
#define GUILD_ID 939501463825170472


typedef struct {
	unsigned long long user_id;
	int random_number;
} PlayerInteraction;

void on_ready(struct discord *client, const struct discord_ready *event) {
	for (int i = 0; i < sizeof(globalCommands) / sizeof(SlashCommands); i++) {
		struct discord_create_guild_application_command params = {
			.name = globalCommands[i].name,
			.description = globalCommands[i].description
		};
		discord_create_guild_application_command(client, event->application->id, GUILD_ID, &params, NULL);
	}
}
 
void on_interaction(struct discord *client, const struct discord_interaction *event) {
    if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND)
        return; /* return if interaction isn't a slash command */
 
	for (int i = 0; i < sizeof(globalCommands) / sizeof(SlashCommands); i++) {
		if (strcmp(event->data->name, globalCommands[i].name) == 0) {
			globalCommands[i].event(client, event);
		}
	}
}
 
int main(void) {
    struct discord *client = discord_init(BOT_TOKEN);
	init_commands();
    discord_set_on_ready(client, &on_ready);
    discord_set_on_interaction_create(client, &on_interaction);
    discord_run(client);
}
