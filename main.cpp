#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include "functions.hpp"
#include "Graph.hpp"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "rus");

    string groups_file_name = R"(D:\CLionProjects\mephi_lab_graph\group_list.txt)";
    string matrix_file_name = R"(D:\CLionProjects\mephi_lab_graph\adjacency_matrix.txt)";

    auto matrix = read_adjacency_matrix(matrix_file_name);
    auto groups = read_group_list(groups_file_name);

    Graph<string> groups_graph(matrix, groups);

    string input_file_name = R"(D:\CLionProjects\mephi_lab_graph\input.txt)";
    ifstream fin(input_file_name);

    vector<pair<string, int>> groups_found;
    string group;
    int max_depth;
    int n;

    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> group >> max_depth;
        if (max_depth == -1)
            max_depth = groups_graph.get_size();

        auto reached = groups_graph.find_reachable(group, max_depth);

        for (const auto &k: reached) {
            bool put = true;
            for (int j = 0; j < groups_found.size(); j++) {
                if (k.first == groups_found[j].first) {
                    groups_found[j].second = min(k.second, groups_found[j].second);
                    put = false;
                    break;
                }
            }
            if (put)
                groups_found.push_back(k);
        }
    }

    fin.close();


    string output_file_name = R"(D:\CLionProjects\mephi_lab_graph\output.txt)";

    write_group_list(groups_found, output_file_name);

    return 0;
}
