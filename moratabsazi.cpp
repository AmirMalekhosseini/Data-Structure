#include <iostream>
#include <vector>
#include <algorithm>

int countInversions(std::vector<int>& arr) {
    int inversions = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[i] > arr[j]) {
                ++inversions;
            }
        }
    }
    return inversions;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int m = countInversions(arr), k = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            std::swap(arr[i], arr[j]);
            int invCount = countInversions(arr);
            if (invCount < m) {
                m = invCount;
                k = 0;
            } else if (invCount == m) {
                ++k;
            }
            std::swap(arr[i], arr[j]); // Swap back to original order
        }
    }

    std::cout << m << " " << k + 1 << std::endl;

    return 0;
}