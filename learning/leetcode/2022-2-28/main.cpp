#include "../include.h"
#include <algorithm>
#include <stack>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

vector<int> put_list_in_arr(ListNode*head)
{
  auto arr = vector<int>{};
  if (head == nullptr) {
    return arr;
  }
  auto cur = head;
  while (cur!=nullptr) {
    arr.push_back(cur->val);
    cur= cur->next;
  }

  return arr;
}

ListNode* reorder_list(ListNode* head)
{
  auto arr = put_list_in_arr(head);
  auto len = arr.size();
  if (len==0) {
    return head;
  }

  auto cur = head,last=head;
  for(int i=0;i<len/2;i++)
  {
    auto temp = new ListNode(arr[len-i-1],cur->next);
    cur->next = temp;
    cur = temp->next;
    last = temp;
  }

  if (len/2==0) {
    last->next = nullptr;
  }else {
  cur->next = nullptr;
  }
  return head;
}


int eval_reverse_polish_notation(vector<string> tokens )
{
  auto istack = stack<int>{};
  for (auto const& token : tokens) {
    if (!(token=="+"||token=="-"||token=="*"||token=="/")) {
      int num = stoi(token);
      istack.push(num);
    }else {
      auto op = token;
      auto num1=istack.top();
      istack.pop();
      auto num2=istack.top();
      istack.pop();

      if (op=="*") {
        istack.push(num1*num2);
      }else if (op=="/") {
        istack.push(num1/num2);
      }else if (op=="+") {
        istack.push(num1+num2);
      }else if (op=="-") {
        istack.push(num1-num2);
      }
    }
  }
  return istack.top();
}

int mini_delete(string str)
{
  int a_count=0,b_count=0,res=0;
  for(int i=0;i<str.size();i++)
  {
    if (str[i]=='a') {
      a_count++;
    }
  }

  res =a_count;
  for(int i=0;i<str.size();i++)
  {
    if (str[i]=='a') {
      a_count--;
    }else {
    b_count++;
    }

    res = min(a_count,b_count);
  }

  return res;
}


//string mini_remove_to_make_valid(string str)
//{
  //auto res = vector<char>{};
  //int opens = 0;
  //for(int i=0;i<str.size();i++)
  //{
    //if (str[i]==')') {
      //opens++;
    //}else if (str[i]=='(') {
      //if ( opens==0 ){
        //continue;
      //}
      //opens--;
    //}
    //res.push_back(str[i]);
  //}
  //for(int i=str.size()-1;i>=0;i++)
  //{

  //}
//}

vector<TreeNode*> get_posible_tree(vector<int> arr)
{

}

