#include "myGraph.h"

/*
 * stack functions
 */

void push(int item)
{
	stack[++top] = item;
}

int pop()
{
	return stack[top--];
}

int peek()
{
	return stack[top];
}

bool isStackEmpty()
{
	return top == -1;
}

/*
 * queue fucntions
 */

void insert(int data)
{
	queue[++back] = data;
	queueItemCount++;
}

int removeData()
{
	queueItemCount--;
	return queue[front++];
}

bool isQueueEmpty()
{
	return queueItemCount == 0;
}

/*
 * graph functions
 */

/* add vertex to the vertex list */
void addVertex(int label)
{
	struct Vertex* vertex = (struct Vertex*) malloc(sizeof(struct Vertex));
	vertex-> label = label;
	vertex-> visited = false;
	listVertices[vertexCount++] = vertex;
}

/* add edge to adge array */
void addEdge(int start, int stop, int dir)
{
	if (dir == 1)
		adjMatrix[start-1][stop-1] = 1;
	if (dir == -1)
		adjMatrix[stop-1][start-1] = 1;
}

/* display the vertex */
void displayVertex(int vertexIndex)
{
	printf("%d ", listVertices[vertexIndex]-> label);
}

/* get the adjacency unvisited vertex */
int getAdjUnvisitedVertex(int vertexIndex)
{
	int i;
	for (i = 0; i < vertexCount; i++)
	{
		if (adjMatrix[vertexIndex][i] == 1 && listVertices[i]-> visited == false){
			return i;
		}
	}
	return -1;
}

/* depth first search */
void DFS()
{
	int i;
	/* mask first node as visited */
	listVertices[0]-> visited = true;
	
	/* display the vertex */
	displayVertex(0);
	
	/* push vertex index in stack */
	push(0);
	
	while (0 == isStackEmpty())
	{
		/* get the unvisited vertex whick is at top of the stack */
		int unvisitedVertex = getAdjUnvisitedVertex(peek());
		
		/* no adjacency vertex found */
		if (-1 == unvisitedVertex)
			pop();
		else{
			listVertices[unvisitedVertex]-> visited = true;
			displayVertex(unvisitedVertex);
			push(unvisitedVertex);
		} 
	}
	
	/* when stack is empty, search is complete, reset the visited label */
	for (i = 0; i < vertexCount; i++){
		listVertices[i]-> visited = false;
	}
}

/* breadth first search */
void BFS()
{
	int i;
	/* mask first node as visited */
	listVertices[0]-> visited = true;
	
	/* display the vertex */
	displayVertex(0);
	
	/* insert vertex index in queue */
	insert(0);
	int unvisitedVertex;
	
	while (isQueueEmpty() == 0)
	{
		/* get the unvisited vertex which is at front of the queue */
		int tempVertex = removeData();
		/* no adjacency vertex found */
		while ((unvisitedVertex = getAdjUnvisitedVertex(tempVertex)) != -1)
		{
			listVertices[unvisitedVertex]-> visited = true;
			displayVertex(unvisitedVertex);
			insert(unvisitedVertex);
		}
	}
	/* when queue is empty, search is complete, reset the visited label */
	for (i = 0; i < vertexCount; i++)
		listVertices[i]-> visited = false;
}
