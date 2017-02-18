/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

int main(int argc, char *argv[])
{
	// An array of 4 players, may need to be a pointer if you want it set dynamically
	player players[NUM_PLAYERS];
	
	// Input buffer and and commands
	char buffer[BUFFER_LEN] = { 0 };
	char **tokens[3][BUFFER_LEN];

	char category_entered[BUFFER_LEN];
	int value_entered;

	// Display the game introduction and initialize the questions
	initialize_game();

	// Prompt for players names
	printf("Players, please enter your names\n");
	// initialize each of the players in the array
	// for(int i = 0; i < 4; i++)
	// {
	// 	fgets(buffer, BUFFER_LEN, stdin);
	// 	strcpy(players[i].name, buffer);
	// 	players[i].score = 0;
	// }

	strcpy(players[0].name, "a");
	strcpy(players[1].name, "b");
	strcpy(players[2].name, "c");
	strcpy(players[3].name, "d");
	players[0].score = 0;
	players[1].score = 0;
	players[2].score = 0;
	players[3].score = 0;

	display_categories();
	printf("Please enter a player's name\n");
	// Perform an infinite loop getting command input from users until game ends	
	while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
	{		
		// Execute the game until all questions are answered

		if(player_exists(players, NUM_PLAYERS, strtok(buffer, "\n"))){
			
			printf("Please enter the value\n");
			while (fgets(buffer, BUFFER_LEN, stdin) != NULL){
				value_entered = atoi(buffer);
				if(already_answered(category_entered, value_entered)){
					printf("Question has already been answered or question does not exist\n");
				} else {
					break;
				}
				printf("Please enter the value\n");
			}
			display_question(category_entered, value_entered);
			while (fgets(buffer, BUFFER_LEN, stdin) != NULL){
				tokenize(buffer, tokens);
				if(valid_answer(category_entered, value_entered, **tokens)){
					break;
				}
				display_question(category_entered, value_entered);
			}
		}
		display_categories();
		// Call functions from the questions and players source files
	}
	// Display the final results and exit
	show_results(players, NUM_PLAYERS);
	return EXIT_SUCCESS;
}

void tokenize(char *input, char **tokens)
{	
	*tokens = strtok(input, " ");
	if(strcasecmp(*tokens, "what") == 0 || strcasecmp(*tokens, "who") == 0){
		*tokens = strtok(NULL, " ");
		printf("%s\n", *tokens);
		if(strcasecmp(*tokens, "is") == 0){
			*tokens = strtok(NULL, " ?\n");
			printf("%s\n", *tokens);
			return;
		}
	}
	printf("Answer is incorrect\n");
}

void show_results(player *players, int num_players)
{
	player temp_player;
	for(int i = 0; i < num_players - 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(players[i].score > players[i+1].score)
			{
				temp_player = players[i];
				players[i] = players[i + 1];
				players[i + 1] = temp_player;
			}
		}
	}

	for(int i = 0; i < NUM_PLAYERS; i++)
	{
		printf("%s %d\n", players[i].name, players[i].score);
	}
}

bool valid_category(char *category, char **category_entered){
	printf("Please enter a category\n");
	while (fgets(buffer, BUFFER_LEN, stdin) != NULL){
		strcpy(category_entered, buffer);
		for(int i = 0; i < NUM_CATEGORIES; i++){
			if(strcasecmp(strtok(category_entered, "\n"), categories[i]) == 0){
				break;
			}else if(i == NUM_CATEGORIES - 1){
				printf("Category entered does not exist\n");
				printf("Please enter a category\n");
			}
		}
	}
}