#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

size_t num_nodes;
size_t num_edges;
vector<vector<pair<size_t, size_t>>> adj_list;

vector<size_t> split(const string &str);


int main() {
    // Parsing input:
    string raw_inp;
    getline(cin, raw_inp);
    vector<size_t> split_inp = split(raw_inp);

    num_nodes = split_inp[0];
    num_edges = split_inp[1];

    // Initialize adjacency list:
    adj_list = vector<vector<pair<size_t, size_t>>>();

    // Form Adj List from verts:
    for (size_t i = 0; i < num_edges; ++i) {
        getline(cin, raw_inp);
        split_inp = split(raw_inp);
        adj_list[split_inp[0] - 1].emplace_back(split_inp[1] - 1, split_inp[2] - 1);
    }
}

vector<size_t> split(const string &str) {
    size_t space = str.find(" ");
    if (space == string::npos) return vector<size_t>();
    string s1 = str.substr(0, space);
    string s2 = str.substr(space, str.length() - 1);
    vector<size_t> split_ints(2);
    split_ints[0] = stoull(s1);
    split_ints[1] = stoull(s2);
    return split_ints;
}