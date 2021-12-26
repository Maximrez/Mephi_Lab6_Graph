#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Graph.hpp"

using namespace std;

pair<int, int> date_to_int(const string &date) {
    string first = date.substr(0, date.find('.'));
    string second = date.substr(date.find('.') + 1);
    int a = stoi(first);
    int b = stoi(second);
    return make_pair(a, b);
}

int count_days_passed(int day1, int month1, int day2, int month2) {
    vector<int> days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (month1 < month2) {
        day2 += days_in_month[month1 - 1];
        month1++;
    }
    return day2 - day1;
}

int count_week_day(int week_day, int days_passed) {
    while (days_passed > 0) {
        week_day--;
        if (week_day == -1)
            week_day = 6;
        days_passed--;
    }
    return week_day;
}

int farthest_week_day(int week_day, int wd1, int wd2) {
    while ((week_day != wd1) and (week_day != wd2)) {
        week_day--;
        if (week_day == -1)
            week_day = 6;
    }
    if (week_day == wd1)
        return wd2;
    return wd1;
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

vector<pair<Edge<string>, pair<int, string>>> read_edges(const string &edges_file_name) {
    ifstream fin(edges_file_name);
    vector<pair<Edge<string>, pair<int, string>>> edges;
    string g1, g2, time;
    int wd;
    fin >> g1;
    while (g1 != ".") {
        fin >> g2 >> wd >> time;
        edges.emplace_back(Edge<string>(g1, g2), make_pair(wd, time));
        fin >> g1;
    }
    fin.close();
    return edges;
}

void write_group_list(vector<pair<string, pair<int, string>>> &groups, const string &output_file_name) {
    vector<string> week_days = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"};
    ofstream fout(output_file_name);
    for (const auto &i: groups) {
        fout << i.first << " " << week_days[i.second.first];
        if (i.second.second != "00:00")
            fout << " " << i.second.second;
        fout << endl;
    }
    fout.close();
}