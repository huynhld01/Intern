#include <stdio.h>
#include <stdlib.h>

/*
 * define maximum number of vetices in the graph 
 */
#define N 5

/*
 * using an array of pointers to represent adjacency list
 */
struct graph{
	struct node* head[N];
};

/*
 * a structure to store adjacency list nodes of the graph 
 */
struct node{
	int dest;
	struct node* next;
};

/*
 * a structure to store graph edges
 */
struct edge{
	int src, dest;
}; 

/*
 * a structure create an adjacency list
 */
struct graph* graph_create(struct edge edges[], int n)
{
	unsigned i;
	
	/* allocate memory for graph */
	struct graph* graph_t = (struct graph*)malloc(sizeof(struct graph));
	
	/* init head pointer for all vetices */
	for (i = 0; i < N; i++)
		graph_t-> head[i] = NULL;
	
	/* add edges to the directed graph one by one */
	for (i = 0; i < n; i++){
		/* assign source and destination vetices */
		int src = edges[i].src;
		int dest = edges[i].dest;
		
		/* alloccate fow new node of adjacency list from src to dest */
		struct node* new_node = (struct node*)malloc(sizeof(struct node));
		new_node-> dest = dest;
		
		/* point to new node to current head */
		new_node-> next = graph_t-> head[src];
		
		/* point head pointer to new node */
		graph_t-> head[src] = new_node;		
	}
	return graph_t;
}

/*
 * print adjacency list 
 */
void graph_print(struct graph* graph_t)
{
	int i;
	for (i = 0; i < N; i++)
	{
		struct node* ptr = graph_t-> head[i];
		while (ptr != NULL)
		{
			printf("(%d -> %d)\t", i, ptr-> dest);
			ptr = ptr-> next;
		}
		printf("\n");
	}
}

int main()
{
	/* Init adges of the graph */
	struct edge edges[] = {{1, 4}, {1, 2}, {2, 4},{3, 2}, {3, 1}, {4, 3},{4, 2}};
	
	/* calculate number of edges */
	int n = sizeof(edges)/sizeof(edges[0]);
	
	/* create graph from edge */
	struct graph *graph_t  = graph_create(edges, n);
	
	/* print adjacency list represent graph */
	graph_print(graph_t);
	return 0;
}




