#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct
{
	char parent[256];
	char name[256];
	int priority;
	int memory;
}proc;

typedef struct process_tree
{
	proc node;
	struct process_tree* left;
	struct process_tree* right;
}proc_tree;


void insert(proc_tree* root, proc node);
void print_dfs(proc_tree* root);

int main(void)
{
	FILE *f = fopen("processes_tree.txt","r");
	proc_tree* tree = NULL;
	proc process;
	printf("beginning insertion\n");
	while(fscanf(f, "%[^,], %[^,], %d, %d\n", process.parent, process.name, &process.priority, &process.memory) > 0)
	{
		if(process.priority == NULL)
			printf("priority is null\n");
		else
			printf("priorityL %d\n",process.priority);
		if(process.memory == NULL)
			printf("memory is null\n");
		else
			printf("memory: %d\n", process.memory);
		if(process.parent == NULL)
			printf("parent is null\n");
		else
			printf("parent: %s\n",process.parent);
		if(process.name == NULL)
			printf("name is null\n");
		else
			printf("name: %s\n",process.name);
		printf("sadadasdasd\n");
		printf("Inserting %s\n", process.name);
		insert(tree,process);
	}
	fclose(f);
	printf("beggining traversal\n");
	print_dfs(tree);

}

void insert(proc_tree* root, proc node)
{
	if(root == NULL)
	{
		root->node = node;
		root->left = NULL;
		root->right = NULL;
	}
	else if(strcmp(root->left->node.name,node.parent))
	{
		if(root->left->left == NULL)
			root->left->left->node = node;
		else if(root->left->right == NULL)
			root->left->right->node = node;
		else
			printf("Error inserting %s\n",node.name);
	}
	else if(strcmp(root->right->node.name,node.parent))
	{
		if(root->right->left == NULL)
			root->right->left->node = node;
		else if(root->right->right == NULL)
			root->right->right->node = node;
		else
			printf("Error inserting %s\n",node.name);
	}
	else
	{
		insert(root->left,node);
		insert(root->right,node);
	}
}

void print_dfs(proc_tree* root)
{
	if(root == NULL)
		return;
	else
	{
		print_dfs(root->left);
		printf("Parent: %s\nName: %s\nPriority: %d\nMemory: %d\n",root->node.parent,root->node.name,root->node.priority,root->node.memory);
		print_dfs(root->right);
	}
}