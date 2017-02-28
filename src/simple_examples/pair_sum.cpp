/* 
  Example find a pair of numbers into a container which
  the sum of this pair is equal to a number
  https://www.youtube.com/watch?v=XKu_SEDAykw&t=13s
*/
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
  Brute force aproach should be mentioned but is not mandatory
  On this case the time complexity would be O(n^2)
*/
template <typename iterType>
tuple<bool, pair<int, int>> find_pair_brute(iterType iBeg, iterType iEnd, int sum){
  // Default value is false,(-1,-1)
  auto retTuple = make_tuple(false,make_pair(-1,-1));
  
  // The brute force aproach is to find the needed element for each element
  auto iBegBak = iBeg;
  for (; iBeg != iEnd; iBeg++){
    auto val2Find = sum - (*iBeg);
    //cout << "At " << *iBeg << " Val to find is :" << val2Find << endl;
    for (auto iBeg2 = iBegBak; iBeg2 != iEnd; iBeg2++){
      //cout << "At element: " << *iBeg2 << endl;
      // Disconsider the same element
      if (iBeg2 == iBeg){
        //cout << "Same element continue" << endl;
        continue;
      } else {
        if (*iBeg2 == val2Find) {
          // Found value
          //cout << "Found value" << endl;
          // Setup the tuple with flag and pair
          get<0>(retTuple) = true;
          get<1>(retTuple).first = *iBeg;
          get<1>(retTuple).second = *iBeg2;
          return retTuple;
        }
      }
    }
  }
  return retTuple;
}

/*
  Sorted approach
  If you consider that the list is sorted you could use a binary search algorithm
  for each value on the list so the code complexity would be O(N*log(N))
*/
template <typename iterType>
tuple<bool, pair<int, int>> find_pair_sort(iterType iBeg, iterType iEnd, int sum){
  // Default value is false,(-1,-1)
  auto retTuple = make_tuple(false,make_pair(-1,-1));
  auto iBegBak = iBeg;
  
  // Iterate linear on the input vector
  for (; iBeg != iEnd; iBeg++){
    auto val2Find = sum - (*iBeg);
    // Binary search on sorted elements is O(log(N)), but as we're looking 
    // linearly on the array O(N) the total complexity will O(N*log(N))
    if (binary_search (iBegBak, iEnd, val2Find)) {
      get<0>(retTuple) = true;
      get<1>(retTuple).first = *iBeg;
      get<1>(retTuple).second = val2Find;
      return retTuple;
    }
  }
  
  return retTuple;
}

/*
  Optima approach for each element insert into a hash table it's complement, but
  before inserting the complement check if the element (not complement) exist on
  the hash, if it exist the pair has been found.
  
  Hash table has O(1) lookup/insert if hash function has no collision
  So the complexity of this algorithm will be O(n)
*/
template <typename iterType>
tuple<bool, pair<int, int>> find_pair_hash(iterType iBeg, iterType iEnd, int sum){
  // Default value is false,(-1,-1)
  auto retTuple = make_tuple(false,make_pair(-1,-1));
  unordered_set<int> hashSet;
  
  // Iterate linear on the input vector
  for (; iBeg != iEnd; iBeg++){
    // Calculate value to have the sum
    auto val2Find = sum - (*iBeg);
    cout << "At " << *iBeg << " Val to find is :" << val2Find << endl;
    // Check if the value exist on the hash set
    auto itHash = hashSet.find(*iBeg);
    if (itHash == hashSet.end()) {
      // Not found include it's complement to the hash
      hashSet.insert(val2Find);
    } else {
      // The complement that create the sum exist
      get<0>(retTuple) = true;
      get<1>(retTuple).first = *iBeg;
      get<1>(retTuple).second = val2Find;
      return retTuple;
    }
  }
  
  return retTuple;
}

// To execute C++, please define "int main()"
int main() {
  vector<int>v1 = {1,2,3,9};
  vector<int>v2 = {1,2,4,4};
  vector<int>v3 = {1,2,6,4};
  
  // Look for pair that gives some sum
  //auto pSum = find_pair_brute(v2.begin(), v2.end(), 8);
  //auto pSum = find_pair_sort(v2.begin(), v2.end(), 8);
  auto pSum = find_pair_hash(v3.begin(), v3.end(), 8);
  cout << "Pair found:" << get<0>(pSum) << " <" << get<1>(pSum).first << "," << get<1>(pSum).second << ">" << endl;
  
  
  return 0;
}
