#include "../include.h"
#include <algorithm>
#include <map>
#include <stdint.h>
#include <string>
#include <tuple>
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

//int binary_saerch_with_rotate(IntArr const& arr,int target)
//{
  //if(arr.empty())
  //{
    //return -1;
  //}
  //int left=0,right=arr.size();
  //while(left<right){
    //int mid=(left+right)/2;
    //int lvalue=arr[left],rvalue=arr[right],mvalue=arr[mid];

    
  //}
//}
//

int num_tree(int n)
{
  auto dp = IntArr{};
  dp.resize(n+1);
  dp[0]=1;
  dp[1]=1;
  return -1;
}

void inorder(TreeNode* root,IntArr & arr)
{
  if(root==nullptr)
  {
    return;
  }
  inorder(root->left,arr);
  arr.push_back(root->val);
  inorder(root->right,arr);
}

bool is_bst(TreeNode* root)
{
  auto arr = IntArr{};
  inorder(root,arr);
  for(int i=1;i<arr.size();i++)
  {
    if(arr[i-1]<arr[i])
    {
      return false;
    }
  }
  return true;
}

bool is_valid_bst_help(TreeNode*root,int min,int max)
{
  if(root == nullptr)
  {
    return true;
  }
  int val = root->val;
  return val>min && val<max && is_valid_bst_help(root->left,min,val) &&is_valid_bst_help(root->right,val,max);
}


bool is_valid_bst(TreeNode* root)
{
  return  is_valid_bst_help(root,INT32_MIN,INT32_MAX);
}

//tuple<TreeNode*,TreeNode*,TreeNode*> 
//
 //tuple<TreeNode*,TreeNode*,TreeNode*> inorder_traverse(TreeNode* root,TreeNode*pre,TreeNode*first,TreeNode*second)
//{
  //if (root==nullptr) {
    //return make_tuple(pre,first,second);
  //}
   //[pre,first,second] = inorder_traverse(root->left,pre,first,second);

//}
//
//void inorder_traverse(TreeNode* root,TreeNode* pre,
                      //TreeNode** first_ptr,TreeNode** second_ptr)
//{
  //if (root==nullptr) {
    //return;
  //}
  //inorder_traverse(root,pre,first_ptr,second_ptr);
//}
