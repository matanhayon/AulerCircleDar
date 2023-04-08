#ifndef GRAPHS_H
#define GRAPHS_H

#include <iostream>
#include <vector>
#include <list>
#include "Vertex.h"
#include "Arc.h"


class Graph
{
private:
    bool is_directed;
    int num_of_vertices;
    int num_of_arcs;
    vector<list<Arc>> neighborsList;
    vector<Vertex*> vertexes;

public:
    Graph() {
        this->is_directed = false;
        this->num_of_vertices = 0;
        this->num_of_arcs = 0;
    }

    void add_arc(int from, int to) {
        from--;
        to--;
        Vertex* vertex_from = vertexes[from];
        Vertex* vertex_to = vertexes[to];
        neighborsList[from].push_back(vertex_to);
        if (!is_directed)
        {
            neighborsList[to].push_back(vertex_from);
            vertex_from->set_degree(vertex_from->get_degree() + 1); //vertex from degree ++
            vertex_to->set_degree(vertex_to->get_degree() + 1); //vertex to degree ++
        }
        else
        {
            vertex_from->set_out_degree(vertex_from->get_out_degree() + 1);
            vertex_to->set_in_degree(vertex_to->get_in_degree() + 1);
        }
    }

    void updateData(bool i_isDirected, int i_numOfVertices, int i_numOfArcs)
    {
        this->is_directed = i_isDirected;
        this->num_of_vertices = i_numOfVertices;
        this->num_of_arcs = i_numOfArcs;
        this->neighborsList.clear();
        this->neighborsList.resize(num_of_vertices);
        this->vertexes.clear();
        this->vertexes.resize(num_of_vertices);

        for (int i = 0; i < num_of_vertices; i++)
        {
            Vertex* v = new Vertex(i + 1);
            this->vertexes[i] = v;
        }
    }

    bool getIsDirected() const {
        return is_directed;
    }

    int get_num_of_vertices() const {
        return num_of_vertices;
    }

    int get_num_of_arcs() const {
        return num_of_arcs;
    }

    list<Arc> get_neighbors(int vertex) const {
        return neighborsList[vertex];
    }

    void print_is_directed()
    {
        cout << "Is the graph directed: " << (is_directed ? "yes" : "no") << endl;
    }

    void printNeightborsList()
    {
        for (int i = 0; i < num_of_vertices; i++)
        {
            cout << "Vertex " << i + 1 << " neighbors: ";
            for (Arc v : neighborsList[i])
            {
                cout << v.getVertex()->get_id() << " ";
            }
            cout << endl;
        }
    }

    void checkEulilerian()
    {
        if (is_directed)
            this->checkEuilerianForDirectedGraph();
        else
            this->checkEuilerianForUndirectedGraph();
    }

    void visit(Vertex* u)
    {
        int id = u->get_id();
        u->set_colour(Colour::GRAY);
        
        for (auto neighbor : neighborsList[id-1]) 
        {
            if (neighbor.getVertex()->get_colour() == Colour::WHITE)
            {
                visit(neighbor.getVertex());                            //Mark edge?
            }
        }
        u->set_colour(Colour::BLACK);
    }

    void checkEuilerianForDirectedGraph()
    {
        //need to check:
        //strongly connected and in-degree == out-degree
        
        bool isEulerian;
        this->resetVerticesColours();
        if (this->isStronglyConnectedGraph() && this->isInAndOutDegreeEqual())
            isEulerian = true;
        else
            isEulerian = false;

        if (isEulerian)
            cout << "The graph is Eulerian." << endl;
        else
            cout << "The graph is not Eulerian." << endl;
    }

    bool isStronglyConnectedGraph()
    {
        if (!this->isConnectedGraph())
            return false;
        else
        {
            Graph transposeGraph;
            createTransposeGraph(transposeGraph);
            cout << "\nTranspose Graph:\n";
            transposeGraph.printNeightborsList();
            return transposeGraph.isConnectedGraph();
        }
    }

    void createTransposeGraph(Graph& transposeGraph)
    {
         // Create the transpose graph
         transposeGraph.updateData(true, this->num_of_vertices, this->num_of_arcs);

         for (int i = 0; i < this->num_of_vertices; i++)
         {
            // For each vertex in the original graph, add all its outgoing edges in the reverse direction
            Vertex* v = this->vertexes[i];
            for (auto neighbor : neighborsList[i])
            {
               int neighbor_id = neighbor.getVertex()->get_id();
               transposeGraph.add_arc(neighbor_id, v->get_id());
            }
          }   
    }

    bool isInAndOutDegreeEqual()
    {
        for (int i = 0; i < num_of_vertices; i++)
        {
            if (vertexes[i]->get_in_degree() != vertexes[i]->get_out_degree())
                return false;
        }
        return true;
    }

    // checks if an undirected graph is Euilerian, meaning the graph is connected, and all the degrees are even.
    void checkEuilerianForUndirectedGraph()
    {
        bool isEulerian;
        this->resetVerticesColours();
        if (this->isConnectedGraph() && this->areAllDegreesEven())
            isEulerian = true;
        else
            isEulerian = false;
        
        if (isEulerian)
            cout << "The graph is Eulerian." << endl;
        else
            cout << "The graph is not Eulerian." << endl;
    }

    // checks if all the degrees in the graph are even
    bool areAllDegreesEven()
    {
        for(int i = 0 ; i < num_of_vertices ; i++)
        {
            if (vertexes[i]->get_degree() % 2 != 0) // checks if all the degrees are even
                return false;
        }

        return true;
    }

    // checks if a graph is connected
    bool isConnectedGraph()
    {
        bool isConnected = true;
        visit(vertexes[0]);
        for (int i = 0; isConnected && i < num_of_vertices; i++)
        {
            if (vertexes[i]->get_colour() != Colour::BLACK)
                isConnected = false;
        }

        return isConnected;
    }



    void resetVerticesColours()
    {
        for (int i = 0; i < num_of_vertices; i++)
        {
            vertexes[i]->set_colour(Colour::WHITE);
        }
    }



    ~Graph()
    {
        for (Vertex* v : vertexes)
        {
            delete v;
        }
    }
};

#endif // GRAPHS_H