#include<iostream>
#include<vector>
using namespace std;
#include <algorithm>

 vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        if(nums.size() < 3) return result;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size() - 2; i++) {
            if(i > 0 && nums[i] == nums[i - 1]) continue;
            int j = i + 1;
            int k = nums.size() - 1;
            while(j < k) {
                if(nums[i] + nums[j] + nums[k] == 0) {
                    result.push_back({nums[i], nums[j], nums[k]});
                    while(j < k && nums[j] == nums[j + 1]) j++;
                    while(j < k && nums[k] == nums[k - 1]) k--;
                    j++;
                    k--;
                } else if(nums[i] + nums[j] + nums[k] < 0) {
                    j++;
                } else {
                    k--;
                    }
                    return 0;
                }
            }
        }
        return result;
    }

int main() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> result = threeSum(nums);
    for(int i = 0; i < result.size(); i++) {
    vector<vector<int>> result = threeSum(nums);
    for(int i = 0; i < result.size(); i++) {
        cout << "[" << result[i][0] << ", " << result[i][1] << ", " << result[i][2] << "] ";
    }
