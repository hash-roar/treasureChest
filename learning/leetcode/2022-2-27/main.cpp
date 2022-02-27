#include "../include.h"

string get_longest_palindromel(string const & str)
{
  if (str.size()==0) {
    return "";
  }
  int left=0,right=0,pl=0,pr=0;
  int len = str.size();
  while (left< len) {
    while (right+1<len && str[left]== str[right+1]) {
      right++;
    }

    while (left-1>=0&& right<len && str[left-1]==str[right+1]) {
      left--;
      right++;
    }

    if (right-left > right -left) {
      pl = right;
      pr= right;
    }

    left = (left+right)/2+1;
    right = left;
  }
  return str.substr(pl,pr+1);
}

int convert_str_to_inter(string_view str)
{
  if (str.empty()) {
    return -1; //throw error
  }

  return atoi(str.data());

}


vector<string>  letterMap = {
  " ",    //0
  "",     //1
  "abc",  //2
  "def",  //3
  "ghi",  //4
  "jkl",  //5
  "mno",  //6
  "pqrs", //7
  "tuv",  //8
  "wxyz", //9
};

void find_conbination(vector<string>& result, string str, int index, string s)
{
  if (index == str.size()) {
    result.push_back(s);
    return;
  }

  auto num = str[index];
  auto letter = letterMap[num - '0'];
  for (int i = 0; i < letter.size(); i++) {
    find_conbination(result, str, index, s + letter[i]);
  }
}
vector<string> get_str_combination(string const & str)
{
  auto result = vector<string>{};
  if (str.empty()) {
    return result;
  }
  find_conbination(result,str,0,"");
  return result;
}

bool check_words(unordered_map<string, int> const& temp_map)
{
  bool flag = false;
  for (auto const &item : temp_map) {
     if (item.second > 0) {
       flag =false;
       break;
     }
  }
  return flag;
}


IntArr find_sub_combined_str(string const& str,vector<string>const & str_arr)
{
  auto result = IntArr{};
  if (str.empty() || str_arr.empty()) {
    return result;
  }
  auto word_map =  unordered_map<string, int>{};
  for (auto const &item : str_arr) {
    if (word_map.find(item)==word_map.end()) {
      word_map[item]=1;
    }else {
      word_map[item]++;
    }
  }
  auto temp_map = word_map;
  int length=str_arr[0].size(),total_len = str_arr.size();
  for (int i = 0, start = 0; i < str_arr.size() - length + 1 && start < str_arr.size() - length + 1; i++) {
    if (temp_map[str.substr(i,i+length)]>0) {
      temp_map[str.substr(i,i+length)]--;
      if (check_words(temp_map)) {
        result.push_back(start);
        continue;
      }
      i=i+length -1;
    } else {
    start++;
    i =start-1;
    temp_map = word_map;
    }
  }
  return result;
}


ListNode* rotate_list_ktimes(ListNode* head, int k)
{
  if (head==nullptr|| head->next==nullptr || k==0) {
    return head;
  }

  auto new_head = new ListNode(0,head);
  int len =0;

  auto cur = new_head;
  while (cur->next!=nullptr) {
      len++;
      cur = cur->next;
  }
  if (k%len ==0) {
      return head;
  }
  cur->next = head;
  cur = new_head;
  for (int i=len-k%len; i>0; i--) {
      cur = cur->next;
  }

  auto result = new ListNode(0,cur->next);
  cur->next = nullptr;
  return result;
}


ListNode* delete_duplicates(ListNode* head)
{
    auto dummy = new ListNode(0,head);
    for (auto slow=dummy,fast =head; slow->next!=nullptr;) {
        for (fast= slow->next;fast->next!=nullptr&&
                fast->next->val==slow->next->val;fast=fast->next) {
            if (slow->next!=fast) {
                slow->next = fast->next;
            }else {
                slow = slow->next;
            }
        }
    }
    return dummy->next;
}

bool list_has_cycle(ListNode* head)
{
    auto slow = head,fast=head;
    while (fast!=nullptr && fast->next!=nullptr) {
        fast = fast->next->next;
        slow= slow->next;
        if (slow ==fast) {
            return true;
        }
    }

    return false;
}

ListNode* add_two_list(ListNode* l1,ListNode* l2)
{
    auto head = new ListNode(0);
    int n1=0,n2=0,carray=0;
    auto current = head;

    while (l1!=nullptr || l2!=nullptr || carray!=0) {
        if (l1 ==nullptr) {
            n1=0;
        }else {
        n1=l1->val;
        l1 = l1->next;
        }
        if(l2==nullptr)
        {
            n2=0;
        }else {
        n2 = l2->val;
        l2 =l2->next;
        }

        current->next = new ListNode((n1+n2+carray)%10);
        current = current->next;
        carray = (n1+n2+carray)/10;
    }
    return head->next;
}





