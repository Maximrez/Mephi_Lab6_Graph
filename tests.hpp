#pragma once

#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include "functions.hpp"
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
    LessonGraph graph;

    graph.add_vertex("1");
    graph.add_vertex("2");
    graph.add_vertex("3");
    graph.add_vertex("3");

    vector<string> vertices = {"1", "2", "3"};
    vector<Lesson> edges;

    assert(graph.get_vertices() == vertices);
    assert(graph.get_edges() == edges);
}

void test_add_edge() {
    LessonGraph graph;

    graph.add_vertex("1");
    graph.add_vertex("2");
    graph.add_vertex("3");

    graph.add_edge("1", "3", 0, "00:00");
    graph.add_edge("2", "1", 0, "00:00");
    graph.add_edge("2", "2", 0, "00:00");
    graph.add_edge("3", "1", 0, "00:00");

    vector<Lesson> edges = {Lesson("1", "3"), Lesson("1", "2")};

    assert(graph.get_edges() == edges);
}

void test_is_edge() {
    LessonGraph graph;

    graph.add_vertex("1");
    graph.add_vertex("2");
    graph.add_vertex("3");

    graph.add_edge("1", "3", 0, "00:00");
    graph.add_edge("2", "1", 0, "00:00");
    graph.add_edge("2", "2", 0, "00:00");
    graph.add_edge("3", "1", 0, "00:00");

    assert(graph.is_edge("1", "1") == false);
    assert(graph.is_edge("1", "2") == true);
    assert(graph.is_edge("1", "3") == true);

    assert(graph.is_edge("2", "1") == true);
    assert(graph.is_edge("2", "2") == false);
    assert(graph.is_edge("2", "3") == false);

    assert(graph.is_edge("3", "1") == true);
    assert(graph.is_edge("3", "2") == false);
    assert(graph.is_edge("3", "3") == false);
}

void test_functions() {
    assert(date_to_int("26.12") == make_pair(26, 12));
    assert(date_to_int("08.11") == make_pair(8, 11));

    assert(count_days_passed(12, 12, 26, 12) == 14);
    assert(count_days_passed(11, 11, 26, 12) == 45);

    assert(count_week_day(6, 14) == 6);
    assert(count_week_day(6, 45) == 3);

    assert(farthest_week_day(6, 3, 0) == 0);
    assert(farthest_week_day(5, 6, 4) == 6);
}