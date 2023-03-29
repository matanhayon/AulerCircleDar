#ifndef DIRECTED_GRAPH
#define DIRECTED_GRAPH
#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <utility>


class DirectedGraph
{
	int _n;
	int _m;
	vector<list<int>> _neighbours;
public:
	DirectedGraph(int n, int m, vector<pair<int, int>> arcsInput);

};

#endif // !DIRECTED_GRAPH