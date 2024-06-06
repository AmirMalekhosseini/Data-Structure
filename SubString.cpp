#include <iostream>
#include <climits>
#include <string>
#include <vector>

using namespace std;

class CharMap {
private:
    static const int ARRAY_SIZE = 256;
    vector<int> charKeys;
    vector<int> charValues;

public:
    CharMap() : charKeys(ARRAY_SIZE, -1), charValues(ARRAY_SIZE, 0) {}

    void set(char character, int count) {
        charKeys[character] = character;
        charValues[character] = count;
    }

    int get(char character) {
        return charValues[character];
    }

    bool exists(char character) {
        return charKeys[character] != -1;
    }

    void increase(char character) {
        charValues[character]++;
    }

    void decrease(char character) {
        charValues[character]--;
    }

    int totalKeys() {
        int count = 0;
        for (int i = 0; i < ARRAY_SIZE; i++) {
            if (charKeys[i] != -1) {
                count++;
            }
        }
        return count;
    }
};

void addCharacterToMap(CharMap& map, char character) {
    if (map.exists(character)) {
        map.set(character, map.get(character) + 1);
    } else {
        map.set(character, 1);
    }
}

string findMinWindowSubstring(string str, string target) {
    if (str.empty() || target.empty()) return "";

    CharMap targetCharCount;
    for (char c : target) {
        addCharacterToMap(targetCharCount, c);
    }

    CharMap windowCharCount;
    int requiredCharCount = targetCharCount.totalKeys();
    int formedCharCount = 0;

    int left = 0, right = 0;
    int minLength = INT_MAX, minLeftIndex = 0;

    while (right < str.length()) {
        char currentChar = str[right];
        addCharacterToMap(windowCharCount, currentChar);

        if (targetCharCount.exists(currentChar) && windowCharCount.get(currentChar) == targetCharCount.get(currentChar)) {
            formedCharCount++;
        }

        while (left <= right && formedCharCount == requiredCharCount) {
            char leftChar = str[left];

            if (right - left + 1 < minLength) {
                minLength = right - left + 1;
                minLeftIndex = left;
            }

            windowCharCount.decrease(leftChar);
            if (targetCharCount.exists(leftChar) && windowCharCount.get(leftChar) < targetCharCount.get(leftChar)) {
                formedCharCount--;
            }

            left++;
        }

        right++;
    }

    return minLength == INT_MAX ? "" : str.substr(minLeftIndex, minLength);
}

int main() {
    string sourceStr, targetStr;
    getline(cin, sourceStr);
    getline(cin, targetStr);

    string result = findMinWindowSubstring(sourceStr, targetStr);
    cout << result << endl;

    return 0;
}
