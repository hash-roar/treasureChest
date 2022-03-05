#include "../include.h"
#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

using IntArr = vector<int>;
using DouDimensionArr = vector<vector<int>>;

TreeNode* build_tree_help(IntArr const& preoder, int p_start, int p_end,
    IntArr const& inorder, int i_start, int i_end)
{
  if (p_start > p_end || i_start > i_end) {
    return nullptr;
  }

  auto root = new TreeNode(preoder[p_start]);
  int index = 0;

  while (inorder[i_start + index] != preoder[p_start]) {
    index++;
  } //we need insure that  input is correct
  root->left = build_tree_help(preoder, p_start + 1, p_start + index,
      inorder, i_start, i_start + index - 1);
  root->right = build_tree_help(preoder, p_start + index + 1, p_end,
      inorder, i_start + index + 1, i_end);

  return root;
}

TreeNode* build_tree(IntArr const& preoder, IntArr const& inorder)
{
  if (preoder.size() == 0) {
    return nullptr;
  }
  return build_tree_help(preoder, 0, preoder.size() - 1,
      inorder, 0, inorder.size() - 1);
}


vector<string> find_repeate(string str)
{
  auto result = vector<string>{};
  if (str.size()<10) {
    return result;
  }
  auto str_map = map<string,int>{};
  for(int i=0;i<str.size()-10;i++)
  {
    auto tempstr = str.substr(i,i+10);
    if (auto res=str_map.find(tempstr);res!=str_map.end() && res->second==1) {
      result.push_back(tempstr);
    }else {    // this can be changed because map init defualt  value zero
      str_map[tempstr]=0;
    }
    str_map[tempstr]++;
  }
  return result;
}


IntArr get_nth_ugly_num(int n)
{
  auto result = IntArr{};
  if (n<=0) {
    return result;
  }

  int p2=1,p3=1,p5=1;
  result.reserve(n+1);
  result.push_back(0);
  result.push_back(1);
  for(int i=2;i<n;i++)
  {
    int x2=result[p2],x3=result[p3],x5=result[p5];
    result.push_back( min(min(x2,x3),x5)) ;
    if (result[i]==x2) {
      p2++;
    }
    if (result[i]==x3) {
      p2++;
    }
    if (result[i]==x5) {
      p5++;
    }
  } 
  return result;
}



IntArr get_kthtimes_num(IntArr const& arr,int k)
{
  auto result = IntArr{};
  if (arr.size()<k) {
    return result;
  }

  auto num_map = unordered_map<int,int>{};
  for (auto const& num : arr) {
    num_map[num]++;
  }

  auto cmp = [ &num_map](int left,int right){
    return num_map[left]<num_map[right];};
  auto prior_que = priority_queue<int,vector<int>,decltype(cmp)>(cmp);
  for (auto const& map_item : num_map) {
    if (prior_que.size()<k) {
      prior_que.push(map_item.first);
    }else if (map_item.second >num_map[prior_que.top()]) {
      prior_que.pop();
      prior_que.push(map_item.first);
    }
  }
  while (!prior_que.empty()) {
    result.push_back(prior_que.top());
    prior_que.pop();
  }
  return result;
}


