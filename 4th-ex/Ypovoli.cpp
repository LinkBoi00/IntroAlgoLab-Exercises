#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

struct EdgeTypes {
    vector<pair<int, int>> treeEdges;
    vector<pair<int, int>> forwardEdges;
    vector<pair<int, int>> backEdges;
    vector<pair<int, int>> crossEdges;
};

void displayGraph(list<int> graph[], int v) {
    cout << "Graph adjacency list display:" << endl;

    for (int i = 1; i < v; i++) { // start from 1 if it's 1-based
        cout << i << " ---> ";
        for (auto it = graph[i].begin(); it != graph[i].end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
}

void insert_edge(list<int> graph[], int u, int v) {
    graph[u].push_back(v);  // Add edge u -> v
}

void sortGraphAdjacencyList(list<int> graph[], int verticesNum) {
    for (int u = 1; u < verticesNum; u++) {
        vector<int> evenArray, oddArray;

        // Check all vertices connected with an edge from i and split them in odd and even vectors
        for (auto it = graph[u].begin(); it != graph[u].end(); ++it) {
            if (*it % 2 == 0) {
                evenArray.push_back(*it);
            } else {
                oddArray.push_back(*it);
            }
        }

        // Sort the two new arrays in ascending order
        sort(evenArray.begin(), evenArray.end());
        sort(oddArray.begin(), oddArray.end());

        // Push the two new vector elements to the list
        graph[u].clear();
        for (int even : evenArray) {
            graph[u].push_back(even);
        }
        for (int odd : oddArray) {
            graph[u].push_back(odd);
        }
    }
}

void storeEdgeType(int u, int v, vector<int>& discoveryTime, vector<int>& finishTime, EdgeTypes& edgeTypes) {
    if (discoveryTime[v] == 0) {
        // Vertex v was discovered from edge (u,v) => Tree edge
        edgeTypes.treeEdges.push_back({u, v});
    } else if (discoveryTime[u] < discoveryTime[v] && finishTime[v] != 0) {
        // Vertex v is finished and d[u] < d[v] => (u,v) is a forward edge
        edgeTypes.forwardEdges.push_back({u, v});
    } else if (discoveryTime[u] > discoveryTime[v] && finishTime[v] == 0) {
        // Vertex v is not finished and d[u] > d[v] => (u,v) is a back edge
        edgeTypes.backEdges.push_back({u, v});
    } else {
        // Anything else is a cross edge
        edgeTypes.crossEdges.push_back({u, v});
    }
}

void DFS_visit(list<int> graph[], vector<bool>& discovered, int& globalTime, vector<int>& discoveryTime, vector<int>& finishTime, int u, EdgeTypes& edgeTypes) {
    discovered[u] = true;
    globalTime++;
    discoveryTime[u] = globalTime;

    cout << "\nDiscovered vertex: " << u << " at time: " << discoveryTime[u] << endl;

    for (auto it = graph[u].begin(); it != graph[u].end(); ++it) {
        int v = *it;

        storeEdgeType(u, v, discoveryTime, finishTime, edgeTypes);

        if (!discovered[v]) {
            cout << "Going through edge (" << u << ", " << v << ")" << endl;
            DFS_visit(graph, discovered, globalTime, discoveryTime, finishTime, v, edgeTypes);
        }
    }

    globalTime++;
    finishTime[u] = globalTime;
    cout << "Finished vertex " << u << " at time " << globalTime << endl;
    cout << endl;
}

void printEdgeType(vector<pair<int, int>>& edges, string edgeType)
{
    sort(edges.begin(), edges.end());

    cout << edgeType << ":" << endl;
    for (auto& edge : edges) {
        cout << edge.first << " " << edge.second << endl;
    }
}

void DFS(list<int> graph[], int verticesNum) {
    vector<bool> discovered(verticesNum, false);
    vector<int> discoveryTime(verticesNum, 0);
    vector<int> finishTime(verticesNum, 0);
    EdgeTypes edgeTypes;

    int globalTime = 0;

    for (int u = 1; u < verticesNum; u++) {
        if (!discovered[u]) {
            cout << "DFS from edge: " << u << endl;
            DFS_visit(graph, discovered, globalTime, discoveryTime, finishTime, u, edgeTypes);
        }
    }

    cout << "\nVertex discovery and finish times:" << endl;
    for (int u = 1; u < verticesNum; u++) {
        cout << "Vertex " << u << ": discovery time: " << discoveryTime[u] << ", finish time: " << finishTime[u] << endl;
    }

    // Print all edge types
    cout << "\nEdge Types\n" << endl;
    printEdgeType(edgeTypes.treeEdges, "Tree edges");
    printEdgeType(edgeTypes.forwardEdges, "Forward edges");
    printEdgeType(edgeTypes.backEdges, "Back edges");
    printEdgeType(edgeTypes.crossEdges, "Cross edges");

}

int main(int argc, char *argv[]) {
    int v = 10; // Number of vertices (+1 if 1-based indexing)

    // Create an adjacency list representation of the graph
    list<int> graph[v];

    // Insert edges
    insert_edge(graph, 1, 2);
    insert_edge(graph, 1, 4);
    insert_edge(graph, 1, 5);
    insert_edge(graph, 2, 3);
    insert_edge(graph, 2, 6);
    insert_edge(graph, 3, 5);
    insert_edge(graph, 3, 7);
    insert_edge(graph, 4, 6);
    insert_edge(graph, 4, 8);
    insert_edge(graph, 5, 4);
    insert_edge(graph, 5, 6);
    insert_edge(graph, 5, 9);
    insert_edge(graph, 6, 7);
    insert_edge(graph, 6, 9);
    insert_edge(graph, 7, 2);
    insert_edge(graph, 7, 8);
    insert_edge(graph, 8, 1);
    insert_edge(graph, 8, 9);
    insert_edge(graph, 9, 3);
    insert_edge(graph, 9, 4);
    insert_edge(graph, 9, 7);

    // Display the graph
    displayGraph(graph, v);

    // DFS
    sortGraphAdjacencyList(graph, v);
    DFS(graph, v);

    return 0;
}
