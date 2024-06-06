#include <iostream>
#include <string>

using namespace std;

int countOccurrences(const string& text, const string& pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();
    int occurrences = 0;

    for (int i = 0; i <= textLength - patternLength; ++i) {
        bool found = true;
        for (int j = 0; j < patternLength; ++j) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            occurrences++;
        }
    }
    return occurrences;
}

int main() {
    string text, pattern;
    getline(cin, text);
    getline(cin, pattern);

    int occurrences = countOccurrences(text, pattern);
    cout << occurrences << endl;

    return 0;
}
