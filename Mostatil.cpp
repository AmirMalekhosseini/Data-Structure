#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <sstream>

using namespace std;

int findMax(vector<int>& row) {
    stack<int> finalStack;
    int counter = 0;
    int max_So_Far = 0;
    int currentArea = 0;
    int topStack;

    while (counter < row.size()) {
        if (finalStack.empty() || row[finalStack.top()] <= row[counter]) {
            finalStack.push(counter++);
        } else {
            topStack = row[finalStack.top()];
            finalStack.pop();
            currentArea = topStack * (finalStack.empty() ? counter : counter - finalStack.top() - 1);
            max_So_Far = max(max_So_Far, currentArea);
        }
    }

    while (!finalStack.empty()) {
        topStack = row[finalStack.top()];
        finalStack.pop();
        currentArea = topStack * (finalStack.empty() ? counter : counter - finalStack.top() - 1);
        max_So_Far = max(max_So_Far, currentArea);
    }

    return max_So_Far;
}

int maxRectangle(vector<vector<int>>& inputMatrix) {
    int max_So_Far = 0;
    if (inputMatrix.empty()) return max_So_Far;

    max_So_Far = findMax(inputMatrix[0]);

    for (int i = 1; i < inputMatrix.size(); i++) {
        for (int j = 0; j < inputMatrix[i].size(); j++) {
            if (inputMatrix[i][j]) {
                inputMatrix[i][j] += inputMatrix[i - 1][j];
            }
        }
        max_So_Far = max(max_So_Far, findMax(inputMatrix[i]));
    }

    return max_So_Far;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, columns;
    cin >> rows >> columns;
    cin.ignore();  // Ignore the newline after the columns input

    vector<vector<int>> inputMatrix(rows, vector<int>(columns));

    for (int i = 0; i < rows; i++) {
        string line;
        getline(cin, line);
        stringstream input(line);
        for (int j = 0; j < columns; j++) {
            input >> inputMatrix[i][j];
        }
    }

    cout << maxRectangle(inputMatrix) << endl;

    return 0;
}
