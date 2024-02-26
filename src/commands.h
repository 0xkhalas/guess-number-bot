#pragma once
#include <stdio.h>
#include <string.h>
#include <concord/discord.h>

typedef struct {
	char* name;
	char* description;
	void(*event)(struct discord *client, const struct discord_interaction *event);
} SlashCommands;

SlashCommands globalCommands[1] = {0};

void test(struct discord *client, const struct discord_interaction *event) {
	struct discord_interaction_response params = {
		.type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
		.data = &(struct discord_interaction_callback_data){
			.content = "pong"
		}
	};
	discord_create_interaction_response(client, event->id, event->token, &params, NULL);
}

void init_commands() {
	globalCommands[0] = (SlashCommands){.name = "ping", .description = "Use this to pong to much", .event = test};
}
