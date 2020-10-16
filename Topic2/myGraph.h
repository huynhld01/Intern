#ifndef MYGRAPH_H_
#define MYGRAPH_H_



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

struct Vertex{
	int label;
	bool visited;
};

/*
 * stack variables 
 */
int stack[MAX];
int top = -1;

/* 
 * queue variables 
 */
int queue[MAX];
int back = -1;
int front = 0;
int queueItemCount = 0;

/*
 * grap variables 
 */

/* list of vertices */
struct Vertex* listVertices[MAX];

/* adjacency of vertices */
int adjMatrix[MAX][MAX];

/* vertex count */
int vertexCount = 0;

/*
 * stack functions
 */

void push(int item);
int pop();
int peek();
bool isStackEmpty();

/*
 * queue fucntions
 */

void insert(int data);
int removeData();
bool isQueueEmpty();

/*
 * graph functions
 */

/* add vertex to the vertex list */
void addVertex(int label);
/* add edge to adge array */
void addEdge(int start, int stop, int dir);
/* display the vertex */
void displayVertex(int vertexIndex);
/* get the adjacency unvisited vertex */
int getAdjUnvisitedVertex(int vertexIndex);
/* depth first search */
void DFS();
/* breadth first search */
void BFS();



#endif /* _MYGRAPH_H_ */