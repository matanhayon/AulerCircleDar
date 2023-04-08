#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include "Vertex.h"
#include "Graphs.h"

using namespace std;


// Function to read input and create graph object
void read_input_and_update_graph(Graph& graph) {
    bool is_directed;
    int numOfVertices, numOfArcs;

    // Read input
    char c_is_directed;
    cout << "Is the graph directed: y/n" << endl;
    cin >> c_is_directed;
    if (c_is_directed != 'y' && c_is_directed != 'n')
    {
        cout << "invalid input";
        exit(1);
    }
    is_directed = (c_is_directed == 'y');

    cin >> numOfVertices;
    cin >> numOfArcs;
    if (numOfVertices < 1 || numOfArcs < 1)
    {
        cout << "invalid input";
        exit(1);
    }

    // Update graph object
    graph.updateData(is_directed, numOfVertices, numOfArcs);

    // Read arcs and add them to graph
    for (int i = 0; i < numOfArcs; i++) {
        int from, to;
        cin >> from;
        cin >> to;
        graph.add_arc(from, to);
    }
}



int main() {
    // Read input and create graph object
    Graph graph;
    read_input_and_update_graph(graph);

    // Print whether graph is directed or not
    graph.checkEulilerian();
    return 0;
}