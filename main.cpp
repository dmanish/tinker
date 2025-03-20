#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/**
 * Returns the top k largest elements from the given array
 * 
 * @param nums The input array of integers
 * @param k The number of top elements to return
 * @return A vector containing the k largest elements
 */
vector<int> topKElements(vector<int>& nums, int k) {
    // Using a min heap to keep track of k largest elements
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    // Process each element in the array
    for (int num : nums) {
        // Add the element to the heap
        minHeap.push(num);
        
        // If heap size exceeds k, remove the smallest element
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    // Extract the k largest elements from the heap
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }
    
    // Reverse to get elements in descending order
    reverse(result.begin(), result.end());
    
    return result;
}

// Function to print a vector
void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

int main() {
    // Test case 1: Basic case
    vector<int> nums1 = {3, 1, 5, 12, 2, 11};
    int k1 = 3;
    cout << "Test case 1: Find top " << k1 << " elements from: ";
    printVector(nums1);
    vector<int> result1 = topKElements(nums1, k1);
    cout << "Result: ";
    printVector(result1);
    cout << endl;
    
    // Test case 2: K equals array size
    vector<int> nums2 = {5, 7, 9, 11, 13};
    int k2 = 5;
    cout << "Test case 2: Find top " << k2 << " elements from: ";
    printVector(nums2);
    vector<int> result2 = topKElements(nums2, k2);
    cout << "Result: ";
    printVector(result2);
    cout << endl;
    
    // Test case 3: Array with duplicate elements
    vector<int> nums3 = {4, 10, 10, 8, 1, 4, 2, 10};
    int k3 = 4;
    cout << "Test case 3: Find top " << k3 << " elements from: ";
    printVector(nums3);
    vector<int> result3 = topKElements(nums3, k3);
    cout << "Result: ";
    printVector(result3);
    cout << endl;
    
    // Test case 4: K is 1
    vector<int> nums4 = {7, 3, 9, 2, 5};
    int k4 = 1;
    cout << "Test case 4: Find top " << k4 << " element from: ";
    printVector(nums4);
    vector<int> result4 = topKElements(nums4, k4);
    cout << "Result: ";
    printVector(result4);
    
    return 0;
}