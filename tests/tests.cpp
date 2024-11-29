#include <gtest/gtest.h>
#include <lib/bst.h>
#include <vector>

TEST(BST, Sample) {
  BST<int, PreOrder> bst;
  bst.insert(1);
  bool answer = (bst.size() == 1) && (bst.find(1) != nullptr);

  ASSERT_TRUE(answer);
}

TEST(BST, Sample_2_insert) {
  BST<int, PostOrder> bst;
  bst.insert(12398);
  bst.insert(12398);;

  ASSERT_TRUE(bst.find(12398) != nullptr);
}

TEST(BST, SimpleExtrtact) {
  BST<int, PreOrder> bst;
  bst.insert(1);
  bst.extract(1);

  bool answer = (bst.find(1) == nullptr) && (bst.size() == 0);

  ASSERT_TRUE(answer);
}

TEST(BST, DoubleExtract) {
  BST<int, PreOrder> bst;
  bst.insert(1);
  bst.erase(1);
  bst.erase(1);

  bool answer = (bst.find(1) == nullptr) && (bst.size() == 0);

  ASSERT_TRUE(answer);
}

TEST(BST, RootExtract) {
  BST<int, PreOrder> bst;
  bst.insert(1);
  bst.insert(0);
  bst.insert(2);

  bst.erase(0);

  ASSERT_EQ(2, bst.size());
}
TEST(BST, erase_root) {
  BST<int, InOrder, std::greater<int>> a{5, 3, 7, 2, 4, 6, 8};
  a.erase(5);
  // Tree should look like:
  //   3
  //  / \
 // 2   7
  //    / \
 //   4   8
  ASSERT_EQ(a.size(), 6);

}

TEST(BST, merge) {
  BST<int, InOrder> a{5, 6, 7};
  BST<int, InOrder> b{3, 4, 5};
  a.merge(b);
  ASSERT_EQ(a.size(), 5);
}

TEST(BST, erase_leaf_with_one_children) {
  BST<int, InOrder, std::greater<int>> a{5, 3, 7, 2, 4, 6, 8};
  a.erase(6);
      //       5
      //     /   \
      //    3     7
      //   / \     \
      //  2   4     8

  auto it = a.begin();
  auto it2 = a.end();
  std::vector<int> res = {2,3,4,5,7,8};
  std::vector<int> ans;
  while (it != it2){
    ans.push_back(*it);
    ++it;
  }
  ASSERT_EQ(res,ans);
}

TEST(BST, erase_existing_values) {
  BST<int,InOrder> a;
  a.insert(1);
  a.insert(2);
  a.insert(3);
  ASSERT_EQ(a.erase(2), 1);
}


TEST(BST, PostOrder_iterator) {
  BST<int,PostOrder, std::greater<int>> a({5,3,2,4,6});
  //      5
  //    /   \
  //   3     6
  //  / \
  // 2   4
  auto it = a.begin();
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 4);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 6);
  ++it;
  ASSERT_EQ(*it, 5);
}


TEST(BST, copy_operator) {
  BST<int,InOrder> a;
  a.insert(5);
  a.insert(4);
  a.insert(6);
  BST<int,InOrder> b;
  b = a;
  ASSERT_EQ(a.size(), b.size());
}

TEST(BST, PostOrder_String) {
  BST<std::string ,PostOrder, std::greater<>> a({"Ghost","Monapolia","Vector","Dom", "Game"});

  //     Ghost
  //    /      \
  //  Dom       Monapolia
  //     \         /
  //     Game    Vector

  auto it = a.begin();
  ASSERT_EQ(*it, "Game");
  ++it;
  ASSERT_EQ(*it, "Dom");
  ++it;
  ASSERT_EQ(*it, "Vector");
  ++it;
  ASSERT_EQ(*it, "Monapolia");
  ++it;
  ASSERT_EQ(*it, "Ghost");
  ASSERT_EQ(a.size(), 5);
}

TEST(BST, binary_vector){
  BST<std::vector<int>,PostOrder, std::greater<>> a;
  bool flag = sizeof(a);
  a.insert({1, 3, 5});
  ASSERT_TRUE(flag);
  ASSERT_EQ(a.size(), 1);
  a.insert({9, 5, 4, 8});
  a.insert({234, 543, 65432});
  ASSERT_EQ(a.size(), 3);
  a.extract({9, 5, 4, 8});
  ASSERT_EQ(a.size(), 2);
}

TEST(BST, reverse_In){
  BST<int,InOrder> a({63,5,3,2, 8, 6, 765, 98});
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
  std::reverse(res.begin(), res.end());
  ASSERT_EQ(res, ans);
}

TEST(BST, reverse_Post){
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
  std::reverse(res.begin(), res.end());
  ASSERT_EQ(res, ans);
}
TEST(BST, reverse_Pre){
  BST<int,PreOrder> a({63,5,3,2, 8, 6, 765, 98});
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
  std::reverse(res.begin(), res.end());
  ASSERT_EQ(res, ans);
}

TEST(BST, find){
  BST<int,PreOrder> a({63,5,3,2, 8, 6, 765, 98});
  std::find(a.begin(), a.end(), 2);
}