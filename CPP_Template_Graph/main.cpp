#include <iostream>
using namespace std;

#include "TGraph.h"

int main()
{
	TGraph<10> cGraph;

	for (int i = 0; i < 4; i++)
		cGraph.Insert_Vertex();

	cGraph.Insert_Edge(0, 1);
	cGraph.Insert_Edge(0, 2);
	cGraph.Insert_Edge(0, 3);
	cGraph.Insert_Edge(1, 2);
	cGraph.Insert_Edge(2, 3);

	cout << "BFS : ";
	cGraph.DFS(0);
	cGraph.SearchAfter();
	cout << endl;

	return 0;
}