#pragma once

#include <vector>
#include <cassert>
#include <string>
#include <cmath>
#include <random>

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
    if (((e1.a == e2.a) and (e1.b == e2.b)) or ((e1.a == e2.b) and (e1.b == e2.a)))
        return true;
    return false;
}

template<typename T>
bool operator!=(const Edge<T> &e1, const Edge<T> &e2) {
    if (e1 == e2)
        return false;
    return true;
}

template<typename T>
ostream &operator<<(ostream &os, const Edge<T> &e) {
    os << "(" << e.a << ", " << e.b << ")";
    return os;
}

template<typename T>
class Graph {
    vector<T> vertices;
    vector<Edge<T>> edges;
    vector<vector<bool>> matrix;
public:
    Graph() {
        vector<T> v;
        vector<Edge<T>> e;
        vector<vector<bool>> m;

        vertices = v;
        edges = e;
        matrix = m;
    };

    Graph(const vector<vector<bool>> &m, const vector<T> &v) : vertices(v), matrix(m) {
        for (int i = 0; i < vertices.size(); i++)
            for (int j = i + 1; j < vertices.size(); j++)
                if (matrix[i][j]) {
                    Edge<T> e = Edge<T>(vertices[i], vertices[j]);
                    edges.push_back(e);
                }
    };

    int get_size() {
        return vertices.size();
    }

    void add_vertex(const T &v) {
        for (int i = 0; i < vertices.size(); i++)
            if (vertices[i] == v)
                return;

        for (int i = 0; i < vertices.size(); ++i)
            matrix[i].push_back(false);
        matrix.push_back(vector<bool>(vertices.size() + 1, false));

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
        if (a == b)
            return;
        add_vertex(b);

        Edge<T> new_edge(a, b);
        for (int i = 0; i < edges.size(); i++)
            if (edges[i] == new_edge)
                return;
        edges.push_back(new_edge);

        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i] == a) {
                for (int j = i + 1; j < vertices.size(); j++) {
                    if (vertices[j] == b) {
                        matrix[i][j] = true;
                        matrix[j][i] = true;
                        break;
                    }
                }
                break;
            }
            if (vertices[i] == b) {
                for (int j = i + 1; j < vertices.size(); j++) {
                    if (vertices[j] == a) {
                        matrix[i][j] = true;
                        matrix[j][i] = true;
                        break;
                    }
                }
                break;
            }
        }
    }

    vector<T> find_adjacent(const T &v, vector<pair<T, int>> &reached) {
        vector<T> adjacent;
        for (auto i: edges) {
            if (i.a == v) {
                bool put = true;
                for (int j = 0; j < reached.size(); j++) {
                    if (reached[j].first == i.b) {
                        put = false;
                        break;
                    }
                }
                if (put)
                    adjacent.push_back(i.b);
            }
            if (i.b == v) {
                bool put = true;
                for (int j = 0; j < reached.size(); j++) {
                    if (reached[j].first == i.a) {
                        put = false;
                        break;
                    }
                }
                if (put)
                    adjacent.push_back(i.a);
            }
        }
        return adjacent;
    }

    vector<pair<T, int>> find_reachable(const T &v, int max_depth) {
        vector<pair<T, int>> reached;
        int depth = 0;
        reached.push_back(make_pair(v, -1));
        int index = 0;
        int n = 1, m = 0;
        while (index < reached.size()) {
            reached[index].second = depth;
            auto adjacent = find_adjacent(reached[index].first, reached);
            n--;
            m += adjacent.size();
            if (n == 0) {
                depth++;
                if (depth > max_depth)
                    return reached;
                n = m;
                m = 0;
            }
            index++;
            for (auto i: adjacent) {
                reached.push_back(make_pair(i, -1));
            }
        }
        return reached;
    }

    vector<T> get_vertices() {
        return vertices;
    }

    vector<Edge<T>> get_edges() {
        return edges;
    }

    vector<vector<bool>> get_matrix() {
        return matrix;
    }

    ~Graph() = default;
};

template<typename T>
Graph<T> get_random_graph(int n, const vector<T> &vertices = {}) {
    vector<vector<bool>> matrix(n);
    for (int i = 0; i < n; i++) {
        matrix[i].resize(n, false);
        for (int j = i + 1; j < n; j++)
            if (rand() % 2 == 1)
                matrix[i][j] = true;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++)
            if (matrix[j][i])
                matrix[i][j] = true;
    }
    Graph<T> random_graph(matrix, vertices);
    return random_graph;
}