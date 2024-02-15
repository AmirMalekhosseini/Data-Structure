#include <iostream>
#include <vector>

int buyIndex;
int sellIndex;
int maxProfit;

int main() {
    int n;
    std::cin >> n;

    std::vector<int> prices(n);

    for (int i = 0; i < n; i++) {
        std::cin >> prices[i];
    }

    buyIndex = 0;
    sellIndex = 0;
    maxProfit = 0;

    int minPriceIndex = 0;

    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] < prices[minPriceIndex]) {
            minPriceIndex = i;
        } else {
            int currentProfit = prices[i] - prices[minPriceIndex];
            if (currentProfit > maxProfit) {
                buyIndex = minPriceIndex;
                sellIndex = i;
                maxProfit = currentProfit;
            }
        }
    }

    std::cout << buyIndex + 1 << " " << sellIndex + 1 << std::endl;

    return 0;
}