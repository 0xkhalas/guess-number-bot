#pragma once
#include "linked_list.h"
#include <stdio.h>
#include <concord/discord.h>
#include <stdlib.h>
#include <string.h>

typedef uint64_t u64;

typedef struct {
	u64 user_id;
	int random_number;
} PlayerInteraction;

typedef struct {
	char* name;
	char* description;
	void(*event)(struct discord *client, const struct discord_interaction *event);
} SlashCommands;

SlashCommands globalCommands[1] = {0};
LinkedList* players = NULL;

PlayerInteraction* get_player(u64 user_id) {
	if (players == NULL) return NULL;

	int len = len_linkedList(players);

	for (int i = 0; i < len; i++) {
		PlayerInteraction* player = (PlayerInteraction*)(get_linkedList(players, i));

		printf("%p\n", player);

		if (player->user_id == user_id) {
			return player;
		}
	}

	return NULL;
} 

int exist_player(u64 user_id) {
	if (players == NULL) return 0;

	PlayerInteraction* player = get_player(user_id);

	if (player != NULL) {
		return 1;
	}

	return 0;
}

int add_player(u64 user_id) {
	if (players == NULL) return 0;

	if (!exist_player(user_id)) {
		PlayerInteraction* player = (PlayerInteraction*)malloc(sizeof(PlayerInteraction));
		player->user_id = user_id;
		player->random_number = (rand() % 100) + 1;
		printf("%d\n", player->random_number);
		add_linkedList(players, player);
		return 1;
	}

	return 0;
}

void remove_player(u64 user_id) {
	if (players == NULL) return;

	int len = len_linkedList(players);

	for (int i = 0; i < len; i++) {
		PlayerInteraction* player = (PlayerInteraction*)(get_linkedList(players, i));
		if (player->user_id == user_id) {
			remove_linkedList(players, i);
		}
	}
}

void guess_result(struct discord *client, const struct discord_message *event) {
	PlayerInteraction* player;

	if ((player = get_player(event->author->id)) != NULL) {
		if (player->random_number == atoi(event->content)) {
			struct discord_ret_message ret = { .sync = DISCORD_SYNC_FLAG };
			struct discord_create_message params = { .content = "You win" };

			discord_create_message(client, event->channel_id, &params, &ret);

			remove_player(event->author->id);

		} else {
			struct discord_ret_message ret = { .sync = DISCORD_SYNC_FLAG };
			struct discord_create_message params = { .content = "You Lose" };

			discord_create_message(client, event->channel_id, &params, &ret);

			remove_player(event->author->id);
		}
	}	
} 


void guess_command(struct discord *client, const struct discord_interaction *event) {
	int result = add_player(event->member->user->id);

	if (result) {
		struct discord_interaction_response params = {
			.type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
			.data = &(struct discord_interaction_callback_data) {
				.content = "Guess number",
			}
		};
		discord_create_interaction_response(client, event->id, event->token, &params, NULL);
	} else {
		struct discord_interaction_response params = {
			.type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
			.data = &(struct discord_interaction_callback_data){
				.content = "You have one guess first"
			}
		};
		discord_create_interaction_response(client, event->id, event->token, &params, NULL);
	}
}

void init_commands() {
	globalCommands[0] = (SlashCommands){ .name = "guess", .description = "Use this to pong to much", .event = guess_command };
	players = init_linkedList();
}

void free_commands() {
	free_linkedList(players);
}
