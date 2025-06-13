#include <bits/stdc++.h>
using namespace std;

struct Item {
    int value, weight;
    bool operator<(Item other) const {
        return (double)value / weight > (double)other.value / other.weight;
    }
};

double fractionalKnapsack(int W, vector<Item>& items) {
    sort(items.begin(), items.end());
    double totalValue = 0.0;

    for (auto& item : items) {
        if (W == 0) break;
        if (item.weight <= W) {
            W -= item.weight;
            totalValue += item.value;
        } else {
            totalValue += item.value * ((double)W / item.weight);
            W = 0;
        }
    }
    return totalValue;
}

int main() {
    int n, W;
    cin >> n >> W;
    vector<Item> items(n);
    for (int i = 0; i < n; i++) cin >> items[i].value >> items[i].weight;
    cout << fixed << setprecision(2) << "Maximum value = " << fractionalKnapsack(W, items);
    return 0;
}
