#include "../include.h"
#include <algorithm>
#include <stdint.h>

int binary_search_(IntArr const& arr,int target)
{
  if (arr.empty()) {
    return -1;
  }
  int left=0,right = arr.size()-1;
  while (left<=right) {
    int mid = left+(right-left)/2;
    if (arr[mid]>target) {
      left=mid+1;
    }else if (arr[mid]<target) {
      right=mid-1;
    }else {
    return mid;
    }
  }
  return -1;
}

int  remove_element(IntArr &arr,int val)
{
  int lo = 0;
  for (int fa=0; fa<arr.size(); fa++) {
    if (val!=arr[fa]) {
      arr[lo++]=arr[fa];
    }
  }
  return lo;
}

IntArr sort_squre(IntArr const& vec)
{
  auto arr = IntArr(vec.size(),0);
  int pos = arr.size()-1;

  for (int i=0,j=vec.size(); i<=j; ) {
    if (arr[i]*arr[i]<arr[j]*arr[j]) {
      arr[pos--] = arr[j]*arr[j];
      j--;
    }else {
      arr[pos--] = arr[i]*arr[i];
      i--;
    }
  }

  return arr;
  
}

int min_arr_sum(IntArr const& arr,int target)
{
  int result = INT32_MAX;
  int sum=0;
  int start=0;
  int sum_len=0;
  for(int j=0;j<arr.size();j++)
  {
    sum+=arr[j];
    while (sum>=target) {
      sum_len = j-start+1;
      result = result<sum_len ? result : sum_len;
      sum -= arr[start++];
    }
  }
  return result==INT32_MAX?0:result;
}



int main()
{
  return 0;
}
