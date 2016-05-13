#include <iostream>
#include <string>
#include "dl_list.h"

using Pic10B::list;

int main(){
  list<std::string> aList;

  aList.push_back("Abigail");
  aList.push_back("Beatriz");
  aList.push_back("Citlali");
  aList.push_back("Daneli");

  aList.push_front("Xibalba");
  aList.push_front("La Catrina");

  for ( auto l : aList )
    std::cout << l << "\n";
  
  return 0;
}
