#pragma once

#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include "Graph.hpp"

using namespace std;

void test_edge_equal() {
    Edge<int> e1(1, 3);
    Edge<int> e2(1, 2);
    Edge<int> e3(-1, 3);
    Edge<int> e4(2, 1);
    Edge<int> e5(1, 3);

    assert(e1 == e5);
    assert(e1 != e2);
    assert(e1 != e3);
    assert(e1 != e4);
    assert(e1 == e5);
}

void test_add_vertex() {
    Graph<int> graph;

    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(3);

    vector<int> vertices = {1, 2, 3};
    vector<Edge<int>> edges;
    vector<vector<bool>> matrix = {{0, 0, 0},
                                   {0, 0, 0},
                                   {0, 0, 0}};

    assert(graph.get_vertices() == vertices);
    assert(graph.get_edges() == edges);
    assert(graph.get_matrix() == matrix);
}

void test_add_edge() {
    Graph<int> graph;

    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);

    graph.add_edge(1, 3);
    graph.add_edge(2, 1);
    graph.add_edge(2, 2);
    graph.add_edge(3, 1);

    vector<vector<bool>> matrix = {{0, 1, 1},
                                   {1, 0, 0},
                                   {1, 0, 0}};
    vector<Edge<int>> edges = {Edge<int>(1, 3), Edge<int>(1, 2)};

    assert(graph.get_edges() == edges);
    assert(graph.get_matrix() == matrix);
}

void test_is_edge() {
    Graph<int> graph;

    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);

    graph.add_edge(1, 3);
    graph.add_edge(2, 1);
    graph.add_edge(2, 2);
    graph.add_edge(3, 1);

    assert(graph.is_edge(1, 1) == false);
    assert(graph.is_edge(1, 2) == true);
    assert(graph.is_edge(1, 3) == true);

    assert(graph.is_edge(2, 1) == true);
    assert(graph.is_edge(2, 2) == false);
    assert(graph.is_edge(2, 3) == false);

    assert(graph.is_edge(3, 1) == true);
    assert(graph.is_edge(3, 2) == false);
    assert(graph.is_edge(3, 3) == false);
}

void test_create_graph() {
    vector<vector<bool>> matrix = {{0, 1, 1, 0, 0},
                                   {1, 0, 1, 0, 0},
                                   {1, 1, 0, 0, 0},
                                   {0, 0, 0, 0, 1},
                                   {0, 0, 0, 1, 0}};

    vector<int> vertices(matrix.size());
    for (int i = 0; i < vertices.size(); i++)
        vertices[i] = i + 1;

    Graph<int> graph(matrix, vertices);

    for (int i = 0; i < vertices.size(); i++)
        for (int j = i + 1; j < vertices.size(); j++)
            assert(graph.is_edge(i + 1, j + 1) == matrix[i][j]);
}

void test_find_reachable() {
    vector<vector<bool>> matrix = {{0, 1, 1, 0, 0, 0},
                                   {1, 0, 1, 0, 0, 1},
                                   {1, 1, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 1, 0},
                                   {0, 0, 0, 1, 0, 0},
                                   {0, 1, 0, 0, 0, 0}};

    vector<int> vertices(matrix.size());
    for (int i = 0; i < vertices.size(); i++)
        vertices[i] = i + 1;

    Graph<int> graph(matrix, vertices);

    vector<pair<int, int>> reached_1 = graph.find_reachable(1, graph.get_size());
    vector<pair<int, int>> answer_1 = {make_pair(1, 0),
                                       make_pair(2, 1),
                                       make_pair(3, 1),
                                       make_pair(6, 2)};
    assert(reached_1 == answer_1);

    vector<pair<int, int>> reached_2 = graph.find_reachable(2, graph.get_size());
    vector<pair<int, int>> answer_2 = {make_pair(2, 0),
                                       make_pair(1, 1),
                                       make_pair(3, 1),
                                       make_pair(6, 1)};
    assert(reached_2 == answer_2);

    vector<pair<int, int>> reached_3 = graph.find_reachable(3, graph.get_size());
    vector<pair<int, int>> answer_3 = {make_pair(3, 0),
                                       make_pair(1, 1),
                                       make_pair(2, 1),
                                       make_pair(6, 2)};
    assert(reached_3 == answer_3);

    vector<pair<int, int>> reached_4 = graph.find_reachable(4, graph.get_size());
    vector<pair<int, int>> answer_4 = {make_pair(4, 0),
                                       make_pair(5, 1)};
    assert(reached_4 == answer_4);

    vector<pair<int, int>> reached_5 = graph.find_reachable(5, graph.get_size());
    vector<pair<int, int>> answer_5 = {make_pair(5, 0),
                                       make_pair(4, 1)};
    assert(reached_5 == answer_5);

    vector<pair<int, int>> reached_6 = graph.find_reachable(6, graph.get_size());
    vector<pair<int, int>> answer_6 = {make_pair(6, 0),
                                       make_pair(2, 1),
                                       make_pair(1, 2),
                                       make_pair(3, 2)};
    assert(reached_6 == answer_6);
}