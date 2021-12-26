#pragma once

#include <vector>
#include <cassert>
#include <string>
#include <cmath>
#include <random>

using namespace std;

// Дуга
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

// Занятие
class Lesson {
    vector<vector<string>> schedule;
public:
    Edge<string> groups;

    explicit Lesson(const Edge<string> &e) : groups(e.a, e.b), schedule(7) {}

    Lesson(const string &group1, const string &group2) : groups(group1, group2), schedule(7) {}

    void add_time(int wd, const string &time) {
        if (schedule[wd].empty()) {
            schedule[wd].insert(schedule[wd].begin(), time);
            return;
        }

        int index = 0;
        while (index < schedule[wd].size()) {
            if (schedule[wd][index] >= time)
                break;
            index++;
        }
        if (index == schedule[wd].size())
            schedule[wd].push_back(time);
        if (schedule[wd][index] > time)
            schedule[wd].insert(schedule[wd].begin() + index, time);
    }

    pair<int, string> find_closest_lesson(int wd1, string time, int wd2) {
        while (wd1 != wd2) {
            for (int i = 0; i < schedule[wd1].size(); i++) {
                if (schedule[wd1][i] >= time)
                    return make_pair(wd1, schedule[wd1][i]);
            }
            wd1 = (wd1 + 1) % 7;
            time = "00:00";
        }
        if (wd2 != -1)
            for (int i = 0; i < schedule[wd2].size(); i++) {
                if (schedule[wd2][i] >= time)
                    return make_pair(wd2, schedule[wd1][i]);
            }
        return make_pair(-1, "");
    }

    ~Lesson() = default;
};

bool operator==(const Lesson &l1, const Lesson &l2) {
    return (l1.groups == l2.groups);
}

bool operator!=(const Lesson &l1, const Lesson &l2) {
    return !(l1 == l2);
}

// Граф групп и занятий
class LessonGraph {
    vector<string> vertices;
    vector<Lesson> edges;
public:
    LessonGraph() {
        vector<string> v;
        vector<Lesson> e;
        vertices = v;
        edges = e;
    };

    LessonGraph(const vector<string> &v, vector<pair<Edge<string>, pair<int, string>>> &e) : vertices(v) {
        for (auto &i: e) {
            bool put = true;
            for (int j = edges.size() - 1; j >= 0; j--)
                if (edges[j].groups == i.first) {
                    edges[j].add_time(i.second.first, i.second.second);
                    put = false;
                    break;
                }
            if (put) {
                Lesson new_lesson(i.first);
                new_lesson.add_time(i.second.first, i.second.second);
                edges.push_back(new_lesson);
            }
        }
    };

    int get_size() {
        return vertices.size();
    }

    void add_vertex(const string &v) {
        for (auto &vertice: vertices)
            if (vertice == v)
                return;

        vertices.push_back(v);
    }

    bool is_edge(const string &a, const string &b) {
        Lesson new_edge(a, b);
        for (auto &edge: edges)
            if (edge == new_edge)
                return true;
        return false;
    }

    void add_edge(const string &a, const string &b, int wd, const string &time) {
        add_vertex(a);
        if (a == b)
            return;
        add_vertex(b);

        Lesson new_edge(a, b);
        new_edge.add_time(wd, time);

        for (auto &edge: edges)
            if (edge == new_edge)
                return;
        edges.push_back(new_edge);
    }

    vector<pair<string, pair<int, string>>> find_adjacent(const pair<string, pair<int, string>> &v, int wd2, const vector<pair<string, pair<int, string>>> &reached) {
        vector<pair<string, pair<int, string>>> adjacent;
        for (auto i: edges) {
            if (i.groups.a == v.first) {
                auto closest_lesson = i.find_closest_lesson(v.second.first, v.second.second, wd2);
                if (closest_lesson.first != -1) {
                    bool put = true;
                    for (const auto &j: reached) {
                        if (j.first == i.groups.b) {
                            put = false;
                            break;
                        }
                    }
                    if (put)
                        adjacent.emplace_back(i.groups.b, closest_lesson);
                }

            }
            if (i.groups.b == v.first) {
                auto closest_lesson = i.find_closest_lesson(v.second.first, v.second.second, wd2);
                if (closest_lesson.first != -1) {
                    bool put = true;
                    for (const auto &j: reached) {
                        if (j.first == i.groups.a) {
                            put = false;
                            break;
                        }
                    }
                    if (put)
                        adjacent.emplace_back(i.groups.a, closest_lesson);
                }

            }
        }
        return adjacent;
    }

    vector<pair<string, pair<int, string>>> find_reachable(const string &v, int wd1, int wd2) {
        vector<pair<string, pair<int, string>>> reached;
        reached.emplace_back(v, make_pair(wd1, "00:00"));
        int index = 0;
        while (index < reached.size()) {
            auto adjacent = find_adjacent(reached[index], wd2, reached);
            index++;
            for (const auto &i: adjacent) {
                reached.push_back(i);
            }
        }
        return reached;
    }

    vector<string> get_vertices() {
        return vertices;
    }

    vector<Lesson> get_edges() {
        return edges;
    }

    ~LessonGraph() = default;
};

//template<typename T>
//Graph<T> get_random_graph(int n, const vector<T> &vertices = {}) {
//    vector<vector<bool>> matrix(n);
//    for (int i = 0; i < n; i++) {
//        matrix[i].resize(n, false);
//        for (int j = i + 1; j < n; j++)
//            if (rand() % 2 == 1)
//                matrix[i][j] = true;
//    }
//
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < i; j++)
//            if (matrix[j][i])
//                matrix[i][j] = true;
//    }
//    Graph<T> random_graph(matrix, vertices);
//    return random_graph;
//}