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
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
	// initialize each question struct and assign it to the questions array
	questions[0] = {"programming","This statement allows you to check a boolean condition.", "What is an if statement?",100,false};
	questions[1] = {"algorithms", "This sorting algorithm is O(n^2).", "What is bubble sort?",100,false};
	questions[2] = {"databases", "This is a prearranged collection of data.", "What is a database.", 100, false};
	questions[3] = {"programming", "This programming paradigm involves lambda calculus.", "What is functional programming?", 200, false};
	questions[4] = {"algorithms", "This is the average case performance of quicksort.", "What is O(nlogn)?", 200, false};
	questions[5] = {"databases", "This person proposed the relational model.", "Who is Edgar F. Codd?", 200, false};
	questions[6] = 


}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
	// print categories and dollar values for each unanswered question in questions array

	for(int i = 0; i < NUM_CATEGORIES; i++)
	{
		printf("%s\t",categories[i]);
	}
	printf("\n");
	for(int i = 0; i < NUM_QUESTIONS; i++)
	{

	}


	
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
	for(int i = 0; i < NUM_QUESTIONS; i++)
	{
		if(strcmp(questions[i].category, category) == 0)
		{
			if(questions[i].value == value)
			{
				printf("%s\n", questions[i].question);
			}
		}
	}
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
	// Look into string comparison functions
	for(int i = 0; i < NUM_QUESTIONS; i++)
	{
		if(strcmp(questions[i].category, category) == 0)
		{
			if(questions[i].value == value)
			{
				if(strcmp(questions[i].answer, answer) == 0)
				{
					return true;
				}else{
					return false;
				}
			}
		}
	}
	return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
	// lookup the question and see if it's already been marked as answered
	for(int i = 0; i < NUM_QUESTIONS; i++)
	{
		if(strcmp(questions[i].category, category) == 0)
		{
			if(questions[i].value == value)
			{
				return questions[i].answered;
			}
		}
	}
	return false;
}
