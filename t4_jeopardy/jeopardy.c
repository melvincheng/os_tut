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
<<<<<<< HEAD
=======
#include <strings.h>
>>>>>>> b951fcdad1f971a7dd5160d3721f80c0813dbedb
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
<<<<<<< HEAD
=======
	char answer_entered[BUFFER_LEN];
	char entered_player[BUFFER_LEN];
>>>>>>> b951fcdad1f971a7dd5160d3721f80c0813dbedb
	int value_entered;

	// Display the game introduction and initialize the questions
	initialize_game();

	// Prompt for players names
	printf("Players, please enter your names\n");
<<<<<<< HEAD
	// initialize each of the players in the array
	// for(int i = 0; i < 4; i++)
	// {
	// 	fgets(buffer, BUFFER_LEN, stdin);
	// 	strcpy(players[i].name, buffer);
	// 	players[i].score = 0;
	// }
=======
	//initialize each of the players in the array
	for(int i = 0; i < NUM_PLAYERS; i++)
	{
		fgets(buffer, BUFFER_LEN, stdin);
	 	strcpy(players[i].name, buffer);
	 	players[i].score = 0;
	}
>>>>>>> b951fcdad1f971a7dd5160d3721f80c0813dbedb

	strcpy(players[0].name, "a");
	strcpy(players[1].name, "b");
	strcpy(players[2].name, "c");
	strcpy(players[3].name, "d");
	players[0].score = 0;
	players[1].score = 0;
	players[2].score = 0;
	players[3].score = 0;

	display_categories();
<<<<<<< HEAD
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
=======
	//loop until all questions are answered
	while(!allAnswered())
	{
		//ask for player name until valid player name is inputted
		printf("Please enter a player's name\n");
		fgets(buffer,BUFFER_LEN, stdin);
		strcpy(entered_player, buffer);
		while(!player_exists(players,NUM_PLAYERS,entered_player))
		{
			printf("Please enter a player's name\n");
			fgets(buffer,BUFFER_LEN, stdin);
			strcpy(entered_player, buffer);	
		}
		//ask player for question category
		printf("Please enter the category\n");
		fgets(buffer,BUFFER_LEN, stdin);
		strcpy(category_entered,buffer);
		while(valid_category(category_entered) != true)
		{
			fgets(buffer,BUFFER_LEN, stdin);
			strcpy(category_entered,buffer);
		}
		//ask player for question value
		printf("Please enter the value\n");
		fgets(buffer,BUFFER_LEN,stdin);
		value_entered = atoi(buffer);
		//loop until unanswered question is chosen
		while(already_answered(category_entered, value_entered))
		{
			printf("Question has already been answered or question does not exist\n");
			printf("Please enter the value\n");
			printf("Please enter the category\n");
			fgets(buffer,BUFFER_LEN, stdin);
			strcpy(category_entered,buffer);
			while(valid_category(category_entered) != true)
			{
				fgets(buffer,BUFFER_LEN, stdin);
				strcpy(category_entered,buffer);
			}
			printf("Please enter the value\n");
			fgets(buffer,BUFFER_LEN,stdin);
			value_entered = atoi(buffer);
		}
		//display chosen question
		display_question(category_entered, value_entered);
		//loop until a player answers the question
		printf("Please enter your answer\n");
		fgets(buffer, BUFFER_LEN, stdin);
		strcpy(answer_entered,buffer);
		while (!valid_answer(category_entered,value_entered,answer_entered)){
				update_score(players,NUM_PLAYERS,entered_player,-1*value_entered);
				display_question(category_entered, value_entered);
				printf("Please enter a player's name\n");
				fgets(buffer,BUFFER_LEN, stdin);
				strcpy(entered_player, buffer);
				while(!player_exists(players,NUM_PLAYERS,entered_player))
				{
					printf("Please enter a player's name\n");
					fgets(buffer,BUFFER_LEN, stdin);
					strcpy(entered_player, buffer);	
				}
				printf("Please enter your answer\n");
				fgets(buffer, BUFFER_LEN, stdin);
				strcpy(answer_entered,buffer);
			}
		update_score(players,NUM_PLAYERS,entered_player,value_entered);
>>>>>>> b951fcdad1f971a7dd5160d3721f80c0813dbedb
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
<<<<<<< HEAD
	printf("Answer is incorrect\n");
=======
	printf("incorrect input\n");
>>>>>>> b951fcdad1f971a7dd5160d3721f80c0813dbedb
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

<<<<<<< HEAD
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
=======
bool valid_category(char *category_entered){
	for(int i = 0; i < NUM_CATEGORIES; i++){
		if(strcasecmp(category_entered, categories[i]) == 10){
			return true;
		}
	}
	printf("Category entered does not exist\n");
	printf("Please enter a category\n");
	return false;
>>>>>>> b951fcdad1f971a7dd5160d3721f80c0813dbedb
}