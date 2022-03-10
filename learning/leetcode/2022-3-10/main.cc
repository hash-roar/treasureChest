#include "../include.h"
#include <algorithm>
#include <queue>
using namespace std;

DouDimensionArr traverse_tree_level(TreeNode* root)
{
  auto result =DouDimensionArr{};
  if (root==nullptr) {
    return result;
  }
  auto que = queue<TreeNode*>{};
  que.push(root);
  while (!que.empty()) {
    int len = que.size();
    auto temp = IntArr{};
    for(int i=0;i<len;i++)
    {
      if(que.front()->left!=nullptr)
      {
        que.push(que.front()->left);
      }else if (que.front()->right!=nullptr) {
        que.push(que.front()->right);
      }

      temp.push_back(que.front()->val);
      que.pop();
    }
    result.push_back(move(temp));
  }
  return result;
}

int get_h_index(IntArr const& vec)
{
  auto arr = vec;
  sort(arr.begin(),arr.end());
  int h_inedx =0;
  for(int i=arr.size();i>0;i--)
  {
    if (arr[i]>arr.size()-i) {
      h_inedx++;
    }else {
    break;
    }
  }
  return h_inedx;
}




int main()
{

  return 0;
}
