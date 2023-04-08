#ifndef arc
#define arc
#include "Vertex.h"
#include <iostream>
#include <vector>
#include <list>

class Arc
{
private:
    Vertex* vertex;
    bool isVisited;

public:
    Arc(Vertex* i_vertex = nullptr, bool i_isVisited = false)
    {
        vertex = i_vertex;
        isVisited = i_isVisited;
    }

    // Getters
    Vertex* getVertex() const
    {
        return vertex;
    }

    bool getIsVisited() const
    {
        return isVisited;
    }

    // Setters
    void setVertex(Vertex* i_vertex)
    {
        vertex = i_vertex;
    }

    void setIsVisited(bool i_isVisited)
    {
        isVisited = i_isVisited;
    }
};

#endif // !arc
