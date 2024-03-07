#include <iostream>
#include <vector>
#include <algorithm>

const int size = 500;
long long totalSum;
int dataCube[size][size][size];
int numRows, numCols, numLayers, numIterations;


bool checkFeasibility(int i, int j, int k) {
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            for (int z = -1; z <= 1; z++) {
                if ((i + x >= 0) && (i + x <= numRows) &&
                    (j + y >= 0) && (j + y <= numCols) &&
                    (k + z >= 0) && (k + z <= numLayers) &&
                    !(x == 0 && y == 0 && z == 0)) {
                    if (dataCube[i][j][k] <= dataCube[i + x][j + y][k + z]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}


void solve() {

    std::vector<int> validValues;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            for (int k = 0; k < numLayers; k++) {
                if (checkFeasibility(i, j, k)) {
                    validValues.push_back(dataCube[i][j][k]);
                }
            }
        }
    }

    sort(validValues.begin(), validValues.end());

    while (numIterations && validValues.size()) {
        numIterations--;
        totalSum += validValues.back();
        validValues.pop_back();
    }
}

void readInput() {

    std::cin >> numRows >> numCols >> numLayers >> numIterations;
    for (int i = 0; i < numLayers; i++) {
        for (int j = 0; j < numRows; j++) {
            for (int k = 0; k < numCols; k++) {
                std::cin >> dataCube[j][k][i];
            }
        }
    }

}

int main() {
    readInput();
    solve();
    std::cout << totalSum << std::endl;
}
