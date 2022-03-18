#include "../include.h"
#include <stack>

using namespace std;
class queue_impeletedby_stack
{
  public:
    queue_impeletedby_stack()
    {
      st_in_ = stack<int>{};
      st_out_=stack<int>{};
    }
  private:

    stack<int>st_in_;
    stack<int>st_out_;

};

bool correct_brackets(string const& str)
{
  auto sta = stack<char>{};

}

int main()
{
  return 0;
}


