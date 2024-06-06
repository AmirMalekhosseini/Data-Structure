#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    
    vector<int> result(n, -1);
    set<int> sortedSet;

    for (int i = n - 1; i >= 0; --i) {
        auto it = sortedSet.upper_bound(numbers[i]);
        if (it != sortedSet.end()) {
            result[i] = *it;
        }
        sortedSet.insert(numbers[i]);
    }
    
    for (int i = 0; i < n; ++i) {
        cout << result[i] << " ";
    }

    return 0;
}
