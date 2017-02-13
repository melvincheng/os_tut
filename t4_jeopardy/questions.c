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
<<<<<<< HEAD
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
=======
	strcpy(questions[0].category, "programming");
	strcpy(questions[0].question, "This statement allows you to check a boolean condition.");
	strcpy(questions[0].answer, "an if statement?");
	questions[0].value = 100,
	questions[0].answered = false;
	strcpy(questions[1].category, "algorithms");
	strcpy(questions[1].question, "This sorting algorithm is O(n^2).");
	strcpy(questions[1].answer, "bubble sort?");
	questions[1].value = 100,
	questions[1].answered = false;
	strcpy(questions[2].category, "databases");
	strcpy(questions[2].question, "This is a prearranged collection of data.");
	strcpy(questions[2].answer, "a database.");
	questions[2].value = 100, 
	questions[2].answered = false;
	strcpy(questions[3].category, "programming");
	strcpy(questions[3].question, "This programming paradigm involves lambda calculus.");
	strcpy(questions[3].answer, "functional programming?");
	questions[3].value = 200, 
	questions[3].answered = false;
	strcpy(questions[4].category, "algorithms");
	strcpy(questions[4].question, "This is the average case performance of quicksort.");
	strcpy(questions[4].answer, "O(nlogn)?");
	questions[4].value = 200, 
	questions[4].answered = false;
	strcpy(questions[5].category, "databases");
	strcpy(questions[5].question, "This person proposed the relational model.");
	strcpy(questions[5].answer, "Edgar F. Codd?");
	questions[5].value = 200, 
	questions[5].answered = false;
	strcpy(questions[6].category, "programming");
	strcpy(questions[6].question, "This was the first programming language.");
	strcpy(questions[6].answer, "FORTRAN?");
	questions[6].value = 300, 
	questions[6].answered = false;
	strcpy(questions[7].category, "algorithms");
	strcpy(questions[7].question, "This form of algorithm makes the locally optimal choice at each step in hopes of a maximized solution.");
	strcpy(questions[7].answer, "a greedy algorithm?");
	questions[7].value = 300, 
	questions[7].answered = false;
	strcpy(questions[8].category, "databases");
	strcpy(questions[8].question, "This is a query run by a query.");
	strcpy(questions[8].answer, "sub-query?");
	questions[8].value = 300,
	questions[8].answered = false;
	strcpy(questions[9].category, "programming");
	strcpy(questions[9].question, "This procedure involves a function calling itself until a base case is reached.");
	strcpy(questions[9].answer, "recursion?");
	questions[9].value = 400, 
	questions[9].answered = false;
	strcpy(questions[10].category, "algorithms");
	strcpy(questions[10].question, "This word is used to describe problems that cannot be realistically solved.");
	strcpy(questions[10].answer, "intractable?");
	questions[10].value = 400, 
	questions[10].answered = false;
	strcpy(questions[11].category, "databases");
	strcpy(questions[11].question, "This word describes a set of entries with similar attriutes.");
	strcpy(questions[11].answer, "entity type?");
	questions[11].value = 400, 
	questions[11].answered = false;
>>>>>>> 6df93c3d639a861dfd730bc145af8fd15dcfefe4
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
	// print categories and dollar values for each unanswered question in questions array
	int v = 100;
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
<<<<<<< HEAD
	printf("\n");
	for(int i = 0; i < NUM_QUESTIONS; i++)
	{
		printf("   %d\t\t",v);
		if(i%3==0)
		{
			printf("\n");
			v+=100;
		}
	}


	
=======
>>>>>>> 6df93c3d639a861dfd730bc145af8fd15dcfefe4
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
