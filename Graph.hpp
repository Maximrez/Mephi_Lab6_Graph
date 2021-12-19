#pragma once

#include <vector>
#include <cassert>
#include <string>
#include <set>

using namespace std;

template<typename T>
struct Edge {
    T a = 0;
    T b = 0;

    Edge(T a, T b) : a(a), b(b) {};

    ~Edge() = default;
};

template<typename T>
bool operator==(const Edge<T> &e1, const Edge<T> &e2) {
    if ((e1.a == e2.a) and (e1.b == e2.b))
        return true;
    return false;
}

template<typename T>
class Graph {
public:
    vector<T> vertices;
    vector<Edge<T>> edges;

    Graph(const vector<vector<bool>> &matrix, const vector<T> &v) : vertices(v) {
        for (int i = 0; i < vertices.size(); i++)
            for (int j = i + 1; j < vertices.size(); j++)
                if (matrix[i][j]) {
                    Edge<T> e = Edge<string>(vertices[i], vertices[j]);
                    edges.push_back(e);
                }
    };

    void add_vertex(const T &v) {
        for (int i = 0; i < vertices.size(); i++)
            if (vertices[i] == v)
                return;

        vertices.push_back(v);
    }

    bool is_edge(const T &a, const T &b) {
        Edge<T> new_edge(a, b);
        for (int i = 0; i < edges.size(); i++)
            if (edges[i] == new_edge)
                return true;
        return false;
    }

    void add_edge(const T &a, const T &b) {
        add_vertex(a);
        add_vertex(b);
        if (a == b)
            return;
        Edge<T> new_edge(a, b);
        for (int i = 0; i < edges.size(); i++)
            if (edges[i] == new_edge)
                return;
        edges.push_back(new_edge);
    }

    set<T> find_reachable(const T &v, set<T> &reached) {
        auto it = reached.find(v);
        if (it != reached.end())
            return reached;
        reached.insert(v);
        for (auto i: edges) {
            if (i.a == v)
                reached = find_reachable(i.b, reached);
            if (i.b == v)
                reached = find_reachable(i.a, reached);
        }
        return reached;
    }


    ~Graph() = default;
};