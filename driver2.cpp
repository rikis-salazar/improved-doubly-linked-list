/** Program to test example implementation of a the list class */
// Student version will test standard list class

#include "dl_list.h"
//#include <list>
#include <iostream>
#include <ostream>
using std::cout;
#include <stdexcept>
using Pic10B::list;
//using std::list;

int main() {
  
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
  bool passed = false;
  try {
    *--list1.begin() = 0;
  } catch (std::invalid_argument& ex) {
    passed = true;
    cout << "Out of range negative index test passed\n";
  }
  if (!passed)
    cout << "Out of range negative index test failed\n";
  passed = false;
  try {
    *list1.end() = 0;
  } catch (std::invalid_argument& ex) {
    passed = true;
    cout << "Out of range index too large test passed\n";
  }
  if (!passed)
    cout << "Out of range index too large test failed\n";
  return 0;
}
