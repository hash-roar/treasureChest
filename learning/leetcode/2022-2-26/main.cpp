#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

using IntArr = vector<int>;
using DouDimensionArr = vector<vector<int>>;

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

//vector<string> get_pair(int n)
//{
  //auto result = vector<string>();
  
  //auto func = [&result,n](int Lremain,int Rremian,string str){
    //if (str.size()==2*n) {
      //result.push_back(str);
      //return ;
    //}
    //if(Lremain>0){
      //func(Lremain,Rremian,str+"(");
    //}
  //};
//}

struct pos{
  int x;
  int y;
};

bool check_soduku(DouDimensionArr const &board, pos position, int val)
{
  for (int i=0;i<board[0].size();i++ ) {
    if (board[position.x][i]!='.' 
        && board[position.x][i]-'0'==val ) {
      return false;
    }
  }
  for (int i=0;i<board.size();i++ ) {
    if (board[i][position.y]!='.' 
        && (board[i][position.y]-'0')==val ) {
      return false;
    }
  }

  auto posx=position.x,posy= position.y;

  for (int i=posx; i<posx+3;i++) {
    for (int j=posy; j<posy+3; j++) {
      if (board[i][j]!='.' &&
          (board[i][j]-'0') ==val)  {
        return false;
      }
    }
  }
  return true;
}

  void putSudoku
(DouDimensionArr & board,vector<pos> positions,int index,bool *succ)
{
  if (*succ ==true) {
    return;
  }
  if (index ==positions.size()) {
    *succ= true;
    return;
  }

  for (int i=0; i<10; i++) {
    if (check_soduku(board,positions[index],i)&& !*succ) {
      board[positions[index].x][positions[index].y] = i;
      putSudoku(board,positions,index+1,succ);
      if ( *succ==true ){
        return;
      }
      board[positions[index].x][positions[index].y]='.';
    }
  }
}

void solveSudoku(DouDimensionArr & board)
{
    if (board.empty()) {
      return;
    }
    auto positions =vector<pos>{};
    bool find = false;
    for(int i=0;i<board.size();i++)
    {
      for(int j=0;j<board[0].size();j++)
      {
        if (board[i][j]=='.') {
          positions.push_back(pos{i,j});
        }
      }
    }
    putSudoku(board, positions, 0, &find);
}


void findcombinationSum(IntArr& arr,int target,int index,IntArr &c,DouDimensionArr& result)
{
  if (target<=0) {
    if (target == 0) {
      result.push_back(c);
    }
    return;
  }
  
  for(int i=0;i<arr.size();i++)
  {
    if (arr[i]>target) {
      break;
    }
    c.push_back(arr[i]);
    findcombinationSum(arr,  target-arr[i], index, c, result);
    c.pop_back();
  }
}

DouDimensionArr combinationSum(IntArr const &vec,int target)
{
  auto result = DouDimensionArr{};
  auto c = IntArr{};
  auto arr = vec;
  if (arr.empty()) {
      return result;
  }

  sort(arr.begin(),arr.end());

  findcombinationSum(arr,target,0,c,result);
  
  return result;
}






int main()
{

  return 0;
}
