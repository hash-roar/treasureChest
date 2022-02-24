#include <iostream>
#include <vector>

using namespace std;

int maxArea(const vector<int>& arr){
  auto max = 0,start=0,end =static_cast<int>(arr.size());
  while (start<end) {
    auto width = end-start;
    auto hight= 0;

    if (arr[start]<arr[end]) {
      hight = arr[start];
      start++;
    }else {
      hight =arr[end];
      end--;
    }
    auto temp = hight*width;
    if (temp > max) {
      max =temp;
    }
  }
    return max;
}


int  main(){

  return 0;
}
