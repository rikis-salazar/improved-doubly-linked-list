/** 
    Technical program that tests the improved  
    doubly linked list class.
*/

#include "dl_list.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

using std::cout;
using Pic10B::list;

int main(){
  
  // Create a list with integers from 0 to 19
  // and use an iterator to traverse the list 
  // and verify that the stored values are 
  // indeed integers from 0 to 19.
  list<int> list1;
  for (int i = 0; i < 20; i++) {
    list1.push_back(i);
  }
  bool pass = true;
  list<int>::iterator itr1 = list1.begin();
  for (int i = 0; i < 20; i++) {
    if (i != *itr1) {
      cout << i << " != list1[" << i << "] == "
	   << *itr1 << '\n';
      pass = false;
    }
    ++itr1;
  }
  if (pass)
    cout << "Index test passed\n";
  

  // Create a list with even integers from 0 to 18
  // and use an iterator to insert all the missing
  // odd integers between 0 and 19. As before, we 
  // use an iterator to traverse the list and verify
  // that it contains all integers between 0 an 19.
  list<int> list2;
  for (int i = 0; i < 20; i += 2) {
    list2.push_back(i);
  }
  list<int>::iterator itr2 = list2.begin();
  for (int i = 0; i < 20; i += 2) {
    list2.insert(++itr2, i+1);
  }
  pass = true;
  itr2 = list2.begin();
  for (int i = 0; i < 20; i++) {
    if (i != *itr2) {
      cout << i << " != list2[" << i << "] == "
	   << *itr2 << '\n';
      pass = false;
    }
    ++itr2;
  }
  if (pass)
    cout << "Insert test passed\n";


  // Next we check for 'out of bound errors'
  bool passed = false;
  try {
    *--list1.begin() = 0;
  } 
  catch (std::invalid_argument& ex) {
    passed = true;
    cout << "Out of range negative index test passed\n";
  }
  // If Pic10B::list is replaced by std::list, this test
  // fails because and exception other than std::invalid_argument 
  // is thrown instead.
  if (!passed)
    cout << "Out of range negative index test failed\n";


  passed = false;
  try {
    *list1.end() = 0;
  } 
  catch (std::invalid_argument& ex) {
    passed = true;
    cout << "Out of range index too large test passed\n";
  }
  if (!passed)
    cout << "Out of range index too large test failed\n";
  return 0;
}
