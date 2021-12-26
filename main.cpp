#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include "functions.hpp"
#include "Graph.hpp"
#include "tests.hpp"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "rus");

    test_edge_equal();
    test_add_vertex();
    test_add_edge();
    test_is_edge();
    test_functions();
    cout << "All tests successfully passed!";

    string groups_file_name = R"(D:\CLionProjects\mephi_lab_graph\group_list.txt)";
    string edges_file_name = R"(D:\CLionProjects\mephi_lab_graph\edges.txt)";

    auto groups = read_group_list(groups_file_name);
    auto edges = read_edges(edges_file_name);

    LessonGraph graph(groups, edges);

    string date = "27.12";
    auto date_pair = date_to_int(date);
    int day = date_pair.first;
    int month = date_pair.second;
    int week_day = 0;

    vector<pair<string, pair<int, string>>> groups_found;

    string input_file_name = R"(D:\CLionProjects\mephi_lab_graph\input.txt)";
    ifstream fin(input_file_name);

    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        string group, date1;
        fin >> group >> date1;
        auto date1_pair = date_to_int(date1);
        int day1 = date1_pair.first;
        int month1 = date1_pair.second;
        int days_passed = count_days_passed(day1, month1, day, month);
        int week_day2 = week_day;
        int week_day1 = count_week_day(week_day2, days_passed);

        if (days_passed > 6) {
            week_day2 = -1;
        }

        auto reached = graph.find_reachable(group, week_day1, week_day2);
        for (const auto &k: reached) {
            bool put = true;
            for (int j = 0; j < groups_found.size(); j++) {
                if (k.first == groups_found[j].first) {
                    if (k.second.first == groups_found[j].second.first) {
                        groups_found[j].second.second = min(k.second.second, groups_found[j].second.second);
                    } else {
                        int farthest_wd = farthest_week_day(week_day, k.second.first, groups_found[j].second.first);
                        groups_found[j].second.first = farthest_wd;
                        if (farthest_wd == k.second.first)
                            groups_found[j].second.second = k.second.second;
                    }
                    put = false;
                    break;
                }
            }
            if (put)
                groups_found.push_back(k);
        }
    }

    string output_file_name = R"(D:\CLionProjects\mephi_lab_graph\output.txt)";

    write_group_list(groups_found, output_file_name);

    return 0;
}