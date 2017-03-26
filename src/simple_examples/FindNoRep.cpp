/*
 * Given a sorted array consisting of only integers where every element appears twice except
 * for one element which appears once. Find this single element that appears only once.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Solution given from leetcode.com
int solutionGiven(vector<int>& nums) {
    int n = nums.size(), left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (mid % 2 == 0) {
            if (nums[mid] == nums[mid-1]) right = mid - 2;
            else if (nums[mid] == nums[mid+1]) left = mid + 2;
            else return nums[mid];
        }
        else {
            if (nums[mid] == nums[mid-1]) left = mid + 1;
            else if (nums[mid] == nums[mid+1]) right = mid - 1;
        }
    }
    return nums[left];
}

// Simple function to print the content of the vector
template <typename T, typename BegIter, typename EndIter>
void printVec(const string &name, BegIter begin, EndIter end){
    size_t numel = 0;
    cout << name << " Elements: [";
    for_each(begin, end, [&](const T &m){cout << m << " ";numel++;});
    cout << "]" << endl;
    cout << "The container has: " << numel << " elements." << endl;
}

// Normal iterative solution
int GetNonRepIterative(const vector<int> &input){
    for (auto it = input.begin(); it < input.end(); ++it){
        auto itFind = find(it+1, input.end(), *it);
        if (itFind == input.end()){
            // Element *begin not found return this number
            return *it;
        } else {
            // Found element, skip block
            it += 1;
        }
    }
}

// Recursive version of the problem
template < typename T, typename BegIter, typename EndIter>
T GetNonRep(BegIter begin, EndIter end){
    // Look for some element (Skiping himself from the list)
    auto itFind = find(begin+1, end, *begin);
    if (itFind == end){
        // Element *begin not found return this number
        return *begin;
    } else {
        // Found element, skip block and try again
        itFind += 1;
        // Every time that the number is found it will return a zero
        return 0 + GetNonRep<T>(itFind, end);
    }
}

int main(){
    vector<int> input1 = {1,1,2,3,3,4,4,8,8};
    int expOut = solutionGiven(input1);
    printVec<int>(string("input1"),input1.begin(), input1.end());
    auto eleNotRep = GetNonRep<int>(input1.begin(), input1.end());
    auto otherResp = GetNonRepIterative(input1);
    cout << "Algo result: " << eleNotRep << " expected result was:" << expOut << endl;
    cout << "Iterative solution:" << otherResp << endl;

    vector<int> input2 = {3,3,7,7,10,11,11};
    expOut = solutionGiven(input2);
    printVec<int>(string("input2"),input2.begin(), input2.end());
    eleNotRep = GetNonRep<int>(input2.begin(), input2.end());
    otherResp = GetNonRepIterative(input2);
    cout << "Algo result: " << eleNotRep << " expected result was:" << expOut << endl;
    cout << "Iterative solution:" << otherResp << endl;

    return 0;
}
