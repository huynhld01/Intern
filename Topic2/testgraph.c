#include "myGraph.h"
#include "myGraph.c"

int main() {
   int i, j;

   for(i = 0; i < MAX; i++){
      for(j = 0; j < MAX; j++)
         adjMatrix[i][j] = 0;
   }


   addVertex(1);   // 0
   addVertex(2);   // 1
   addVertex(3);   // 2
   addVertex(4);   // 3

   //addEdge(1, 2, 1);    // 1 - 2
   //addEdge(1, 4, 1);    // 1 - 4
   //addEdge(2, 4, 1);    // 2 - 4
   //addEdge(3, 1, 1);    // 3 - 1
   //addEdge(3, 2, 1);    // 3 - 2
   //addEdge(4, 2, 1);    // 4 - 2
   //addEdge(4, 3, 1);	  // 4 - 3
	 addEdge(1, 2, 1);    // 1 - 2
	 addEdge(1, 3, 1);    // 1 - 3
     addEdge(2, 3, -1);    // 3 - 2
     addEdge(2, 4, 1);    // 2 - 4
     addEdge(4, 4, 1);    // 4 - 4
   printf("Depth First Search: ");
   DFS(); 
   printf("\nBreadth First Search: ");
   BFS();

   return 0;   
}