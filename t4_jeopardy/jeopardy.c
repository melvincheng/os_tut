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
#include <strings.h>
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

	char category_entered[BUFFER_LEN] = { 0 };
	char answer_entered[BUFFER_LEN] = { 0 };
	char entered_player[BUFFER_LEN] = { 0 };
	int value_entered;

	// Display the game introduction and initialize the questions
	initialize_game();

	// Prompt for players names
	printf("Players, please enter your names\n");
	//initialize each of the players in the array
	for(int i = 0; i < NUM_PLAYERS; i++)
	{
		fgets(buffer, BUFFER_LEN, stdin);
	 	strcpy(players[i].name, strtok(buffer, "\n"));
	 	players[i].score = 0;
	}

	display_categories();
	//loop until all questions are answered
	while(!allAnswered())
	{
		//ask for player name until valid player name is inputted
		printf("Please enter a player's name\n");
		fgets(buffer,BUFFER_LEN, stdin);
		strcpy(entered_player, strtok(buffer, "\n"));
		while(!player_exists(players,NUM_PLAYERS,entered_player))
		{
			printf("Please enter a player's name\n");
			fgets(buffer,BUFFER_LEN, stdin);
			if(strtok(buffer, "\n")){
				strcpy(entered_player, strtok(buffer, "\n"));
			}
		}
		//ask player for question category
		printf("Please enter the category\n");
		fgets(buffer,BUFFER_LEN, stdin);
		strcpy(category_entered, strtok(buffer, "\n"));
		while(!valid_category(category_entered))
		{
			fgets(buffer,BUFFER_LEN, stdin);
			strcpy(category_entered, strtok(buffer, "\n"));
		}
		//ask player for question value
		printf("Please enter the value\n");
		fgets(buffer,BUFFER_LEN,stdin);
		value_entered = atoi(strtok(buffer, "\n"));
		//loop until unanswered question is chosen
		while(already_answered(category_entered, value_entered))
		{
			printf("Question has already been answered or question does not exist\n");
			printf("Please enter the category\n");
			fgets(buffer,BUFFER_LEN, stdin);
			strcpy(category_entered, strtok(buffer, "\n"));
			while(!valid_category(category_entered))
			{
				fgets(buffer,BUFFER_LEN, stdin);
				if(strtok(buffer, "\n")){
					strcpy(category_entered, strtok(buffer, "\n"));
				}
			}
			printf("Please enter the value\n");
			fgets(buffer,BUFFER_LEN,stdin);
			value_entered = atoi(strtok(buffer, "\n"));
		}
		//display chosen question
		display_question(category_entered, value_entered);
		//loop until a player answers the question
		printf("Please enter your answer\n");
		fgets(buffer, BUFFER_LEN, stdin);
		strcpy(answer_entered, strtok(buffer, "\n"));
		while (!valid_answer(category_entered,value_entered,answer_entered)){
				update_score(players,NUM_PLAYERS,entered_player,-1*value_entered);
				display_question(category_entered, value_entered);
				printf("Please enter a player's name\n");
				fgets(buffer,BUFFER_LEN, stdin);
				strcpy(entered_player,  strtok(buffer, "\n"));
				while(!player_exists(players,NUM_PLAYERS,entered_player))
				{
					printf("Please enter a player's name\n");
					fgets(buffer,BUFFER_LEN, stdin);
					strcpy(entered_player,  strtok(buffer, "\n"));	
				}
				printf("Please enter your answer\n");
				fgets(buffer, BUFFER_LEN, stdin);
				strcpy(answer_entered, strtok(buffer, "\n"));
			}
		update_score(players,NUM_PLAYERS,entered_player,value_entered);
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
	printf("incorrect input\n");
}

void show_results(player *players, int num_players)
{
	player temp_player;
	for(int i = 0; i < num_players - 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(players[i].score < players[i+1].score)
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

