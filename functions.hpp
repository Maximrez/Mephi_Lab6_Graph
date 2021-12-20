#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Graph.hpp"

using namespace std;

vector<vector<bool>> read_adjacency_matrix(const string &matrix_file_name) {
    ifstream fin(matrix_file_name);
    int n;
    fin >> n;
    vector<vector<bool>> matrix(n);
    bool t;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            fin >> t;
            matrix[i].push_back(t);
        }
    fin.close();
    return matrix;
}


vector<string> read_group_list(const string &groups_file_name) {
    ifstream fin(groups_file_name);
    int n;
    fin >> n;
    vector<string> groups(n);
    string t;
    for (int i = 0; i < n; i++) {
        fin >> groups[i];
    }
    fin.close();
    return groups;
}

void write_group_list(vector<pair<string, int>> &groups, const string &groups_file_name) {
    ofstream fout(groups_file_name);
    for (const auto &i: groups) {
        fout << i.first << " " << i.second << endl;
    }
    fout.close();
}

template<typename T>
void graph_to_file(Graph<T> graph, const string &file_name) {
    ofstream fout(file_name);
    auto matrix = graph.get_matrix();
    int n = graph.get_size();

    fout << n << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j])
                fout << "1 ";
            else
                fout << "0 ";
        }
        fout << endl;
    }
    fout.close();
}