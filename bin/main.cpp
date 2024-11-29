#include "lib/bst.h"
#include <iostream>


int main() {
  BST<int,PostOrder> a({63,5,3,2, 8, 6, 765, 98});
  auto it = a.begin();
  auto it2 = a.end();
  std::vector<int> ans;
  while (it != it2){
    ans.push_back(*it);
    ++it;
  }
  auto it_ = a.begin();
  auto it_2 = a.end();
  std::vector<int> res;
  while (it_ != it_2){
    --it_2;
    res.push_back(*it_2);
  }
  for (int i = 0; i < res.size(); ++i){
    std::cout << res[i] << " ";
  }

}