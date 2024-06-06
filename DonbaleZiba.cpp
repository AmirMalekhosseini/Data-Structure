#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MySet {
private:
    static const int TABLE_SIZE = 100000;
    vector<vector<int>> table; 
    
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    MySet() {
        table.resize(TABLE_SIZE);
    }

    void insert(int key) {
        int index = hashFunction(key);
        if (!contains(key)) {
            table[index].push_back(key);
        }
    }

    bool contains(int key) {
        int index = hashFunction(key);
        for (int value : table[index]) {
            if (value == key) {
                return true;
            }
        }
        return false;
    }
};

int longestConsecutiveSequence(vector<int>& numbers) {
    MySet numberSet;
    for (int num : numbers) {
        numberSet.insert(num);
    }

    int longestSequence = 0;

    for (int num : numbers) {
        if (!numberSet.contains(num - 1)) {
            int currentNum = num;
            int currentSequence = 1;

            while (numberSet.contains(currentNum + 1)) {
                currentNum++;
                currentSequence++;
            }

            longestSequence = max(longestSequence, currentSequence);
        }
    }

    return longestSequence;
}

int main() {
    int n;
    cin >> n;

    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    int result = longestConsecutiveSequence(numbers);
    cout << result << endl;

    return 0;
}
