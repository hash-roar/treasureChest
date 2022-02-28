#include <cstddef>
#include <algorithm>
#include <list>
#include <unordered_set>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <map>
#include <stdlib.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>
#include <stack>

using namespace std;

using IntArr = vector<int>;
using DouDimensionArr = vector<vector<int>>;

struct ListNode{
  int val;
  ListNode * next;
  ListNode():val(0),next(nullptr){}
  ListNode(int x):val(x),next(nullptr){}
  ListNode(int x,ListNode*next):val(x),next(next){}
};

struct TreeNode{
  int val;
  TreeNode*left;
  TreeNode*right;
  TreeNode(int val=0,TreeNode*left=nullptr,TreeNode*right=nullptr)
    :val(val),left(left),right(right){}
};

template<typename T>
struct ListNodeT
{
  T val;
   ListNodeT* next;
  ListNodeT()=default;
  ListNodeT(T val):val(val),next(nullptr){}
  ListNodeT(T val,ListNodeT* next):val(val),next(next){}
};

//------> utils <--------
template <typename T>
void swap_data(T& a, T& b)
{
  auto temp = a;
  a = b;
  b = a;
}
template <typename T, int SIZE>
void reverse_arr_static(T (&arr)[SIZE])
{
}

template <typename T>
void reverse_arr(T arr[], int start, int end) //dangerous function
{
  while (start < end) {
    swap_data(arr[start], arr[end]);
    start++;
    end--;
  }
}

//------->utils<----------
