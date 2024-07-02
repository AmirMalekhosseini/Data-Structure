#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



int findMaxSubArraySum(const vector<int>& nums) {
    int maxSumSoFar = 0, currentMaxSum = 0;
    int maxElement = nums[0];
    bool allNegative = true;
    
    for (int num : nums) {
        currentMaxSum = max(currentMaxSum + num, 0);
        maxSumSoFar = max(maxSumSoFar, currentMaxSum);

        if (num >= 0) {
            allNegative = false;
        }
        maxElement = max(maxElement, num);
    }

    // If all numbers are negative, return 0
    return allNegative ? 0 : maxSumSoFar;
}

int main() {
    int size;
    cin >> size;
    vector<int> elements(size);
    for (int i = 0; i < size; ++i) {
        cin >> elements[i];
    }
    int maxSubArraySum = findMaxSubArraySum(elements);
    cout << maxSubArraySum << endl;

    return 0;
}
