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
	question q;

	strcpy(q.category,"programming");
	strcpy(q.question,"This statement allows you to check a boolean condition.");
	strcpy(q.answer,"an if statement?");
	q.value = 100;
	q.answered = false;
	questions[0] = q;

	strcpy(q.category,"algorithms");
	strcpy(q.question,"This sorting algorithm is O(n^2).");
	strcpy(q.answer,"bubble sort?");
	questions[1] = q;

	strcpy(q.category,"databases");
	strcpy(q.question,"This is a prearranged collection of data.");
	strcpy(q.answer,"a database?");
	questions[2] = q;

	strcpy(q.category,"programming");
	strcpy(q.question,"This programming paradigm is based off of lambda calculus.");
	strcpy(q.answer,"functional programming?");
	q.value = 200;
	questions[3] = q;

	strcpy(q.category,"algorithms");
	strcpy(q.question,"This is the average case performance of quicksort.");
	strcpy(q.answer,"O(nlogn)?");
	questions[4] = q;

	strcpy(q.category,"databases");
	strcpy(q.question,"This person proposed the relational model.");
	strcpy(q.answer,"Edgar F. Codd?");
	questions[5] = q;

	strcpy(q.category,"programming");
	strcpy(q.question,"This was the first programming language.");
	strcpy(q.answer, "FORTRAN?");
	q.value = 300;
	questions[6] = q;

	strcpy(q.category,"algorithms");
	strcpy(q.question,"This form of algorithm makes the locally optimal choice at each step in hopes of a maximized solution.");
	strcpy(q.answer,"a greedy algorithm?");
	questions[7] = q;

	strcpy(q.category,"databases");
	strcpy(q.question, "This is a query run by a query.");
	strcpy(q.answer,"sub-query?");	
	questions[8] = q;

	strcpy(q.category,"programming");
	strcpy(q.question, "This procedure involves a function calling itself until a base case is reached.");
	strcpy(q.answer,"recursion?");
	q.value = 400;
	questions[9] = q;

	strcpy(q.category,"algorithms");
	strcpy(q.question, "This word is used to describe problems that cannot be realistically solved.");
	strcpy(q.answer,"intractable?");
	questions[10] = q;

	strcpy(q.category,"databases");
	strcpy(q.question, "This word describes a set of entries with similar attriutes.");
	strcpy(q.answer,"entity type?");
	questions[11] = q;
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
	// print categories and dollar values for each unanswered question in questions array
	for(int i = 0; i < NUM_CATEGORIES; i++)
	{
		printf("%s\t",categories[i]);
		for(int j = 0; j < NUM_QUESTIONS; j++){
			if(strcmp(questions[j].category, categories[i]) == 0 && !questions[j].answered){
				printf("%d\t", questions[j].value);
			}
		}
		printf("\n");
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
