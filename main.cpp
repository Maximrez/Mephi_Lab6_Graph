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

    set<string> s;

    string input_file_name = R"(D:\CLionProjects\mephi_lab_graph\input.txt)";
    ifstream fin(input_file_name);
    string group;
    fin >> group;
    fin.close();

    auto reached = groups_graph.find_reachable(group, s);

    string output_file_name = R"(D:\CLionProjects\mephi_lab_graph\output.txt)";

    write_group_list(reached, output_file_name);

    return 0;
}
