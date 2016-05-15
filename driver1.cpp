/** 
   Simple driver for the improved doubly linked list class
*/

#include <iostream>
#include <string>
#include "dl_list.h"

using Pic10B::list;

int main(){
  // Empty list
  list<std::string> aList;

  // Add three items to the back of the list
  aList.push_back("Abigail");
  aList.push_back("Beatriz");
  aList.push_back("Citlali");
  aList.push_back("Daneli");

  // Add two items to the front of the list
  aList.push_front("Xibalba");
  aList.push_front("La Catrina");

  // Use iterator to add new item at position 3 
  list<std::string>::iterator iter = aList.begin();  // iter at position 1
  iter++; // iter at position 2
  aList.insert(++iter, "Candle Maker");
  
  // Use iterator to traverse the list without making changes
  for ( list<std::string>::iterator it = aList.begin(); 
        it != aList.end() ; ++it )
    std::cout << *it << "\n";
  std::cout << "\n";


  /** Using the 'auto' modifier */

  // Attempting to 'mess with' the list 
  std::cout << "Renaming elements???\n";
  for ( auto item : aList )  
     item = "NoName";

  /**
     'auto' asks the compiler to figure out what is the
     type needed for the loop. Compare to

     for ( list<std::string>::iterator it = aList.begin(); 
           it != aList.end() ; ++it )

     where 'item' plays the role of '*it' above.

     and decide which one is more convenient.
  */

  // Oops! Apparently  'auto' didn't work
  for ( auto item : aList )
    std::cout << item << "\n";
  std::cout << "\n";

  // Let's try again
  std::cout << "RENAMING ELEMENTS!!!\n";
  for ( auto& item : aList )  // <-- this time we use a reference instead
     item = "Some Name";

  // Oops! It did not work
  for ( auto item : aList )
    std::cout << item << "\n";

  // Finally, let us 'kill' the list.
  aList.remove("Some Name");

  if ( aList.empty() )
    std::cout << "\nThe list is now empty!\n";

  return 0;
}
