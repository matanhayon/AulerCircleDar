#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(int n, int m, vector<pair<int, int>> arcsInput)
{
	_neighbours.reserve(n);
	_n = n;
	_m  = m;


}