
#include "../include.h"
#include <functional>
#include <unordered_set>

bool is_anagram(string const& s, string const& t)
{
  int record[26] = { 0 };
  for (int i = 0; i < s.size(); i++) {
    record[s[i] - 'a']++;
  }

  for (int i = 0; i < t.size(); i++) {
    record[s[i] - 'a']--;
  }
  for (int i = 0; i < t.size(); i++) {
    if (record[i] != 0) {
      return false;
    }
  }
  return true;
}

IntArr get_array_union(IntArr const& arr1, IntArr const& arr2)
{
  if (arr1.empty() || arr2.empty()) {
    return IntArr {};
  }

  auto result_set = unordered_set<int> {};
  auto hash_map = unordered_set<int>(arr1.begin(), arr1.end());

  for (auto const& item : arr1) {
    if (hash_map.find(item)!=hash_map.end()) {
      result_set.insert(item);
    }
  }

  return IntArr(result_set.begin(),result_set.end());
}

bool can_construct(string const&ransom_node,string const& magazine)
{
  int record[26]={0};
  for(int i=0;i<magazine.length();i++)
  {
    record[magazine[i]-'a']++;
  }

  for(int i=0;i<ransom_node.length();i++)
  {
    record[ransom_node[i]-'a']--;
    if (record[ransom_node[i]-'a']<0) {
      return false;
    }
  }
    
  return true;
}




