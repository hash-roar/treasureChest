#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

using IntArr = vector<int>;

//------> utils <--------
template <typename T>
void swap_data(T& a, T& b)
{
  auto temp = a;
  a = b;
  b = a;
}
template<typename T,int SIZE>
void reverse_arr_static(T (&arr)[SIZE])
{

}

template<typename T>
void reverse_arr(T arr[],int start,int end) //dangerous function
{
  while (start< end) {
    swap_data(arr[start],arr[end]);
    start++;
    end--;
  }
}

//------->utils<----------
IntArr GetNextPermition(IntArr const & vec)
{
  auto arr = vec;
  
  int i=0,j=0;
  for (i=arr.size(); i>=0;i--) {
    if (arr[i]<arr[i+1]) {
      break;
    }
  }

  if (i>=0) {
    for (j=arr.size(); j>i ;j--) {
      if (arr[j]>arr[i]) {
        break;
      }
    }

    swap(arr[i],arr[j]);
  }
  reverse(arr.begin()+i+1,arr.begin()+arr.size());
  return arr;
}



int search_first_eq(IntArr const & arr,int target){
  int lo = 0,hi =arr.size();

  while (lo<hi) {
    auto mid = lo +(hi-lo)/2;

    if (arr[mid]>target) {
      hi = mid-1;
    }else if(arr[mid]<target) {
        lo = mid+1;
    }else {
      if (mid == 0 || arr[mid-1]!=target) {
        return mid;
      }
      hi = mid -1;
    }

  }
  return -1;
}

int search_last_eq(IntArr const & arr,int target)
{
  int lo = 0,hi =arr.size();

  while (lo<hi) {
    auto mid = lo +(hi-lo)/2;

    if (arr[mid]>target) {
      hi = mid-1;
    }else if(arr[mid]<target) {
        lo = mid+1;
    }else {
      if (mid == arr.size()-1 || arr[mid+1]!=target) {
        return mid;
      }
      hi = mid +1;
    }

  }
  return -1;
}

int search_first_greater(IntArr const & arr,int target)
{
  int lo = 0,hi =arr.size();
  while (lo< hi) {
    auto mid = lo + (hi-lo)/2;
    if (arr[mid]>=target) {
      if (mid==0 || arr[mid-1]<target) {
        return mid;
      }
      hi = mid-1;
    }else {
      lo = mid+1;
    }
  }
  return -1;
}

int search_last_less(IntArr const & arr,int target)
{
  int lo = 0,hi =arr.size();
  while (lo< hi) {
    auto mid = lo + (hi-lo)/2;
    if (arr[mid]<=target) {
      if (mid==arr.size()-1 || arr[mid+1]<target) {
        return mid;
      }
      hi = mid+1;
    }else {
      lo = mid-1;
    }
  }
  return -1;

}



pair<int, int> search_range(IntArr const & arr)
{
  auto result = pair<int, int>{-1,-1};
  if (arr.empty()) {
      return result;
  }



}




int main()
{

  return 0;
}
