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
    cout <<"Enter y for directed graph, else n\n";
    cin >> c_is_directed;
    is_directed = (c_is_directed == 'y');

    cout << "Enter number of vertices:\n";
    cin >> numOfVertices;
    cout << "Enter number of arcs:\n";
    cin >> numOfArcs;

    // Update graph object
    graph.updateData(is_directed, numOfVertices, numOfArcs);

    // Read arcs and add them to graph
    for (int i = 0; i < numOfArcs; i++) {
        int from, to;
        cout << "Enter from arc:\n";
        cin >> from;
        cout << "Enter to arc:\n";
        cin >> to;
        graph.add_arc(from, to);
    }
}

int main() {
    // Read input and create graph object
    Graph graph;
    read_input_and_update_graph(graph);

    // Print whether graph is directed or not
    graph.print_is_directed();
    graph.printNeightborsList();
    graph.checkEulilerian();
    return 0;
}