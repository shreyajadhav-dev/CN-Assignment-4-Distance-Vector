#include <iostream>
using namespace std;

#define INF 999

int main() {
int n;

cout << "Enter number of routers: ";
cin >> n;

if (n < 1 || n > 10) {
    cout << "Number of routers must be between 1 and 10." << endl;
    return 1;
}

int cost[10][10], dist[10][10], nextHop[10][10];

cout << "\nEnter the initial network cost matrix:\n";

for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        cin >> cost[i][j];
        dist[i][j] = cost[i][j];

        if (i == j) {
            dist[i][j] = 0;
            nextHop[i][j] = i;
        } else if (cost[i][j] != INF) {
            nextHop[i][j] = j;
        } else {
            nextHop[i][j] = -1;
        }
    }
}

cout << "\n===== INITIAL NETWORK COST MATRIX =====\n";
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (cost[i][j] == INF)
            cout << "INF\t";
        else
            cout << cost[i][j] << "\t";
    }
    cout << endl;
}

cout << "\n===== INITIAL ROUTING TABLES =====\n";
for (int i = 0; i < n; i++) {
    cout << "\nRouter " << i + 1 << ":\n";
    cout << "Destination\tCost\tNext Hop\n";

    for (int j = 0; j < n; j++) {
        cout << j + 1 << "\t\t";

        if (dist[i][j] == INF)
            cout << "INF\t";
        else
            cout << dist[i][j] << "\t";

        if (nextHop[i][j] == -1)
            cout << "-";
        else
            cout << nextHop[i][j] + 1;

        cout << endl;
    }
}

// Calculate minimum costs through intermediate routers
for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][k] != INF && dist[k][j] != INF &&
                dist[i][k] + dist[k][j] < dist[i][j]) {
                dist[i][j] = dist[i][k] + dist[k][j];
                nextHop[i][j] = nextHop[i][k];
            }
        }
    }
}

cout << "\n===== FINAL ROUTING TABLES =====\n";
for (int i = 0; i < n; i++) {
    cout << "\nRouter " << i + 1 << ":\n";
    cout << "Destination\tCost\tNext Hop\n";

    for (int j = 0; j < n; j++) {
        cout << j + 1 << "\t\t";

        if (dist[i][j] == INF)
            cout << "INF\t";
        else
            cout << dist[i][j] << "\t";

        if (nextHop[i][j] == -1)
            cout << "-";
        else
            cout << nextHop[i][j] + 1;

        cout << endl;
    }
}

int source, destination;

cout << "\nEnter source router (1 to " << n << "): ";
cin >> source;
cout << "Enter destination router (1 to " << n << "): ";
cin >> destination;

if (source < 1 || source > n ||
    destination < 1 || destination > n) {
    cout << "Invalid router number." << endl;
    return 1;
}

source--;
destination--;

cout << "\n===== SHORTEST PATH =====\n";

if (dist[source][destination] == INF) {
    cout << "No path exists.\n";
} else {
    cout << "Source: Router " << source + 1 << endl;
    cout << "Destination: Router " << destination + 1 << endl;
    cout << "Minimum Cost: " << dist[source][destination] << endl;

    if (source == destination)
        cout << "Next Hop: Same router" << endl;
    else
        cout << "Next Hop: Router "
             << nextHop[source][destination] + 1 << endl;
}

return 0;

}