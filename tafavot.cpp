#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> arr1(n);
    std::vector<int> arr2(m);

    for (int i = 0; i < n; i++) {
        std::cin >> arr1[i];
    }

    for (int i = 0; i < m; i++) {
        std::cin >> arr2[i];
    }

    std::vector<bool> mapped(m, false); // Keep track of whether an element in arr2 has been mapped

    int max_diff = 0;

    for (int i = 0; i < n; i++) {
        int diff = 0;
        int max_temp_diff = 0;  
        int max_index = 0;  
        for (int j = 0; j < m; j++) {
            int temp_diff = std::abs(arr2[j] - arr1[i]);
            if (!mapped[j] && temp_diff > max_temp_diff) {
                max_temp_diff = temp_diff;
                max_index = j;
            }
        }
        diff = max_temp_diff;
        mapped[max_index] = true;  // Mark the element in arr2 as mapped
        max_diff += diff;
    }

    std::cout << max_diff << std::endl;

    return 0;
}