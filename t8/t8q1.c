#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

typedef struct{
	char parent[256];
	char name[256];
	int priority;
	int memory;
} proc;

typedef struct process_tree{
	struct process_tree *left, *right;
	proc process;
} proc_tree;

void insert(proc temp_proc);
proc_tree *search(char *name, proc_tree *node);
void print_tree(proc_tree *node);



proc_tree *head = NULL;



int main(void){
	FILE *fp;
	fp = fopen("processes_tree.txt", "r");
	proc temp_proc;

	while(fscanf(fp, "%[^,], %[^,], %d, %d\n", temp_proc.parent, temp_proc.name, &temp_proc.priority, &temp_proc.memory) > 0){
		insert(temp_proc);
	}
	fclose(fp);

	print_tree(head);
}

void insert(proc temp_proc){
	proc_tree *temp_node, *child_node;

	child_node = malloc(sizeof(proc_tree));
	child_node->left = NULL;
	child_node->right = NULL;

	child_node->process = temp_proc;


	if(head == NULL){
		head = child_node;
	}else{
		temp_node = search(temp_proc.parent, head);
		if(temp_node != NULL){
			if(temp_node->left == NULL){
				temp_node->left = child_node;
			}else{
				temp_node->right = child_node;
			}
		}else{
			fprintf(stderr, "%s process not found\n", temp_proc.parent);
		}
	}
}

proc_tree *search(char *name, proc_tree *node){
	proc_tree *parent_node = NULL;
	if(head == NULL){
		return NULL;
	}else if(strcmp(node->process.name, name) == 0){
		return node;
	}else{
		if(node->left != NULL){
			parent_node = search(name, node->left);
		}
		if(parent_node == NULL && node->right != NULL){
			parent_node = search(name, node->right);
		}
		return parent_node;
	}
}

void print_tree(proc_tree *node){
	proc temp_proc = node->process;
	printf("Parent: %s\n Name: %s\n Priority: %d\n Memory: %d\n\n", temp_proc.parent, temp_proc.name, temp_proc.priority, temp_proc.memory);
	if(node->left != NULL){
		print_tree(node->left);
	}
	if(node->right != NULL){
		print_tree(node->right);
	}
}