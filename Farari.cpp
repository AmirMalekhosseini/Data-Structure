#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int destination;
    int length;
};

void readGraph(int numberOfEdges, vector<vector<Edge>>& graph) {
    for (int i = 0; i < numberOfEdges; i++) {
        int nodeU, nodeV, edgeLength;
        cin >> nodeU >> nodeV >> edgeLength;
        nodeU--;
        nodeV--;
        graph[nodeU].push_back({nodeV, edgeLength});
        graph[nodeV].push_back({nodeU, edgeLength});
    }
}

void dijkstra(int startNode, const vector<vector<Edge>>& graph, vector<int>& distances) {
    int numberOfNodes = graph.size();
    distances.assign(numberOfNodes, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priorityQueue;
    distances[startNode] = 0;
    priorityQueue.push({0, startNode});

    while (!priorityQueue.empty()) {
        int currentNode = priorityQueue.top().second;
        int currentDistance = priorityQueue.top().first;
        priorityQueue.pop();

        if (currentDistance > distances[currentNode]) continue;

        for (const auto& edge : graph[currentNode]) {
            int neighborNode = edge.destination;
            int edgeLength = edge.length;
            if (distances[currentNode] + edgeLength < distances[neighborNode]) {
                distances[neighborNode] = distances[currentNode] + edgeLength;
                priorityQueue.push({distances[neighborNode], neighborNode});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numberOfNodes, numberOfEdges, personPosition, prizePosition, numberOfPolices;
    cin >> numberOfNodes >> numberOfEdges >> personPosition >> prizePosition >> numberOfPolices;
    
    personPosition--;
    prizePosition--;   
    
    vector<int> policesPosition(numberOfPolices);
    for (int i = 0; i < numberOfPolices; i++) {
        cin >> policesPosition[i];
        policesPosition[i]--;
    }

    vector<vector<Edge>> graph(numberOfNodes);
    readGraph(numberOfEdges, graph);

    vector<int> distancesFromPerson, distancesFromPrize;
    dijkstra(personPosition, graph, distancesFromPerson);
    dijkstra(prizePosition, graph, distancesFromPrize);

    int distancePersonToPrize = distancesFromPerson[prizePosition];

    bool isPersonShortest = true;
    for (int otherPersonPosition : policesPosition) {
        if (distancesFromPrize[otherPersonPosition] < distancePersonToPrize) {
            isPersonShortest = false;
            break;
        }
    }

    if (isPersonShortest) {
        cout << distancePersonToPrize << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
