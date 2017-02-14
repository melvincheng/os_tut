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

	// Display the game introduction and initialize the questions
	initialize_game();

	// Prompt for players names
	printf("Players, please enter your names\n");
	// initialize each of the players in the array
	for(int i = 0; i < 4; i++)
	{
		fgets(buffer, BUFFER_LEN, stdin);
		strcpy(players[i].name, buffer);
		players[i].score = 0;
	}
	display_categories();
	// Perform an infinite loop getting command input from users until game ends
	while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
	{		
		// Execute the game until all questions are answered
		char **tokens = NULL;
		tokenize(buffer,tokens);
		display_categories(tokens[0],tokens[1]);
		

		// Call functions from the questions and players source files
		display_categories();
		// Display the final results and exit
		show_results(players);
	}
	return EXIT_SUCCESS;
}

void tokenize(char *input, char **tokens)
{
	int i = 0;
	char* token = strtok(input, " ");
	printf("%s\n",token );
	tokens[i++] = token;
	while(token != NULL)
	{
		token = strtok(input," ");
		printf("%s\n",token );
		tokens[i++] = token;
	}
}

void show_results(player *players)
{
	player temp_player;
	for(int i = 0; i < NUM_PLAYERS - 1; i++)
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