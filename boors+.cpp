#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> prices(n);

    for (int i = 0; i < n; i++) {
        std::cin >> prices[i];
    }

    int maxProfit = 0;
    int numMaxProfitIndexes = 0;
    std::vector<std::pair<int, int>> maxProfitIndexes;

    int minPriceIndex = 0;
    int buyIndex = 0;
    int sellIndex = 0;

    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] < prices[minPriceIndex]) {
            minPriceIndex = i;
        } else {
            int currentProfit = prices[i] - prices[minPriceIndex];
            if (currentProfit > maxProfit) {
                maxProfit = currentProfit;
                buyIndex = minPriceIndex;
                sellIndex = i;
                numMaxProfitIndexes = 1;
                maxProfitIndexes.clear();
                maxProfitIndexes.push_back({buyIndex, sellIndex});
            } else if (currentProfit == maxProfit) {
                numMaxProfitIndexes++;
                maxProfitIndexes.push_back({minPriceIndex, i});
            }
        }
    }

    std::cout << numMaxProfitIndexes << std::endl;
    for (int i = 0; i < maxProfitIndexes.size(); i++) {
        std::cout << maxProfitIndexes[i].first + 1 << " " << maxProfitIndexes[i].second + 1 << std::endl;
    }

    return 0;
}