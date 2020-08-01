#include <iostream>
#include <cstdbool>
#include <vector>
#include <string>
#include <utility>
#include <queue>
using namespace std;

size_t num_nodes;
size_t num_edges;
vector<vector<pair<size_t, size_t>>> adj_list;
vector<size_t> dist;
vector<size_t> parent;
vector<bool> processed;
vector<size_t> heap_under;
priority_queue<size_t, vector<size_t>, greater<size_t>> heap;


vector<size_t> split(const string &str, bool begin);


int main() {
    // Parsing input:
    string raw_inp;
    getline(cin, raw_inp);
    vector<size_t> split_inp = split(raw_inp, true);

    num_nodes = split_inp[0];
    num_edges = split_inp[1];

    // Initialize adjacency list:
    adj_list = vector<vector<pair<size_t, size_t>>>(num_nodes, vector<pair<size_t, size_t>>());

    // Form Adj List from verts:
    for (size_t i = 0; i < num_edges; ++i) {
        getline(cin, raw_inp);
        split_inp = split(raw_inp, false);
        pair<size_t, size_t> insert = pair<size_t, size_t>(split_inp[1] - 1, split_inp[2]);
        adj_list[split_inp[0] - 1].push_back(insert);
    }
    // Do Dijkstra starting from vertex 1 (indexed at 0):
    dist = vector<size_t>(num_nodes, SIZE_MAX);
    parent = vector<size_t>(num_nodes, NULL);
    heap_under = vector<size_t>(num_nodes, SIZE_MAX);
    processed = vector<bool>(num_nodes, false);

    dist[0] = 0;
    heap_under[0] = 0;
    heap = priority_queue<size_t, vector<size_t>, greater<size_t>>();
    for (size_t i = 0; i < num_nodes; ++i) heap.push(dist[i]);
    while(!heap.empty()){
        size_t v = heap.top();
        for (auto i = adj_list[v].begin(); i != adj_list[v].end(); ++i){
            size_t nbr = i->first;
            size_t weight = i->second;
            if (dist[nbr] > dist[v] + weight){
                dist[nbr] = dist[v] + weight;
                parent[nbr] = v;
                heap_under[nbr] = dist[nbr];
            }
        }
        processed[v] = true;
        priority_queue<size_t, vector<size_t>, greater<size_t>> nheap = priority_queue<size_t, vector<size_t>, greater<size_t>>();
        for (size_t i = 0; i < num_nodes; ++i) if(!processed[i]) nheap.push(dist[i]);
        heap = nheap;
    }
    size_t path = num_nodes - 1;
    size_t parched_count = 0;
    while (path){
        size_t p = parent[path];
        if (dist[path] - dist[p] == 2) ++parched_count;
        path = p;
    }
    if (parched_count) cout << parched_count;
    else cout << "-1";

    return 0;
}

vector<size_t> split(const string &str, bool begin) {
    vector<size_t> split_ints;
    if (begin){
        split_ints = vector<size_t>(2);
        size_t space = str.find(" ");
        if (space == string::npos) return vector<size_t>();
        string s1 = str.substr(0, space);
        string s2 = str.substr(space, str.length() - 1);
        split_ints[0] = stoull(s1);
        split_ints[1] = stoull(s2);
    }
    else{
        split_ints = vector<size_t>(3);
        size_t space = str.find(" ");
        size_t space2 = str.find(" ", space + 1);
        if (space == string::npos) return vector<size_t>();
        string s1 = str.substr(0, space);
        string s2 = str.substr(space, space2);
        string s3 = str.substr(space2, str.length() - 1);
        split_ints[0] = stoull(s1);
        split_ints[1] = stoull(s2);
        split_ints[2] = stoull(s3);
    }

    return split_ints;
}