






















#include <stdio.h>
int main(){
	int node, node1, node2, n_edge, d;
	scanf("%d", &node);
	int matrix[node][node];
	
	/* Inittializing matrix value */
	for (int i = 0; i < node; i++)
		for (int j = 0; j < node; j++)
			matrix[i][j] = 0;
	scanf("%d", &n_edge);
	
	for (int i = 0; i < n_edge; i++){
		scanf("%d%d%d", &node1, &node2, &d);
		if (d == 1)
			matrix[node1-1][node2-1] = 1;
		if (d == -1)
			matrix[node2-1][node1-1] = 1;
	
	}
	
	/* print */
	for (int i = 0; i < node; i++)
	{
		for (int j = 0; j < node; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n ");
	}
	return 0;
}
