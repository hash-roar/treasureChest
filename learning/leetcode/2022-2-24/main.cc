#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <vector>

using namespace std;

using DouDimArr = vector<vector<int>>;
using IntArr = vector<int>;

int maxArea(const vector<int>& arr)
{
  auto max = 0, start = 0, end = static_cast<int>(arr.size());
  while (start < end) {
    auto width = end - start;
    auto hight = 0;

    if (arr[start] < arr[end]) {
      hight = arr[start];
      start++;
    } else {
      hight = arr[end];
      end--;
    }
    auto temp = hight * width;
    if (temp > max) {
      max = temp;
    }
  }
  return max;
}

auto three_sum_zero(const vector<int>& arr)
{
  int length = static_cast<int>(arr.size());
  auto result = DouDimArr();
  if (length < 3) {
    return result;
  }
  auto vec = arr;
  sort(vec.begin(), vec.end());

  for (int i = 0; i < length; i++) {
    if (vec[i] > 0) {
      return result;
    }
    if (i > 0  and vec[i] == vec[i - 1]) {
      continue;
    }
    auto L = i + 1, R = i - 1;

    while (L < R) {
      if (vec[i] + vec[R] + vec[L] == 0) {
        result.push_back(vector { vec[i], vec[L], vec[R] });
        while (L < R and vec[L] == vec[L + 1]) {
          L += 1;
        }
        while (L < R and vec[R - 1] == vec[R]) {
          R -= 1;
        }

        L += 1;
        R -= 1;
      } else if (vec[i] + vec[L] + vec[R] > 0) {
        R -= 1;
      } else {
        L += 1;
      }
    }
  }
  return result;
}

auto three_sum_cloest(const IntArr& arr,int target)
{
  int length = static_cast<int>(arr.size());
  int result =0 ;
  if (length<3) {
    return result;
  }
  int diff = INT32_MAX;
  auto vec = arr;
  sort(vec.begin(),vec.end());

  for (int i=0;i<length-2;i++) {
    
    if (i>0 && vec[i]==vec[i-1]) {
      continue;
    }

    auto j=i+1,k=length-1;
    while (j<k) {
      auto sum = vec[i]+arr[j]+vec[k];
      if (abs(sum -target)<diff) {
        result=sum;
        diff = abs(sum-target);
      }

      if (sum == target) {
        return result;
      }else if (sum > target) {
        k--;
      }else {
        j++;
      }

    }
  }
  return result;
}
  





int main()
{

  return 0;
}
