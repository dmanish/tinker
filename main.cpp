#include<unordered_map>
#include<iostream>
#include <queue>

using namespace std;

vector<int> TopkFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }

    priority_queue<pair<int, int>> pq;
    for (auto it = freq.begin(); it != freq.end(); it++) {
        pq.push({it->second, it->first});
    }

    vector<int> res;
    for (int i = 0; i < k; i++) {
        res.push_back(pq.top().second);
        pq.pop();
    }

    return res;
}   

int main() {
    vector<int> nums = {1, 1, 1, 2, 2, 3,7,7,7,7,7,8,2,7,2};
    int k = 2;
    vector<int> res = TopkFrequent(nums, k);
    for (int num : res) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}