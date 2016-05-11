#ifndef __IMPROVED_DL_LIST_H__
#define __IMPROVED_DL_LIST_H__

#include <algorithm>  // std::swap, std::size_t
#include <stdexcept>  // std::invalid_argument

namespace Pic10B{

  template <typename ItemType>
  class list{
    private:
      // Nested 'NestedNode' class (see nested_node.h)
      #include "nested_node.h"

    public:
      // Nested 'iterator' class (see nested_list_iterator.h)
      // Make it a friend...
      // Nested 'const iterator' class (see nested_const_list_iterator.h)
      // Make it a friend...

    private:
      // Data fields
      NestedNode* head;
      NestedNode* tail;
      std::size_t num_items;   // <-- optional

    public:
      /** Member functions */
      // Default constructor
      list() { 
        head = tail = nullptr; 
	num_items = 0; 
      } 

      // Copy constructor
      list( const list<ItemType>& source );

      // Destructor
      ~list(){
        while ( head != nullptr ){
	  NestedNode* current_node = head;
	  head = head->next;
	  delete current_node;
	}
	tail = nullptr;
	num_items = 0;
      }

      // Assignment operator
      list<ItemType>& operator=( list<ItemType> rhs ){ // <-- By value???
          this->swap(rhs);
	  return *this;  // <-- rhs goes out of scope here
      }


      /** Some other basic functions */
      void push_front( const ItemType& theData ){
        head = new NestedNode(theData, nullptr, head);
	if ( head->next != nullptr )
	  head->next->prev = head;
	if ( tail == nullptr )  // <-- The list was empty
	  tail = head;
	num_items++;
	return;
      }

      void push_back( const ItemType& theData ){
	if ( tail != nullptr ){
	  tail->next =  new NestedNode(theData, tail, nullptr);
	  tail = tail->next;
	  num_items++;
	}
	else
	  push_front(theData);  //  numItems is increased as well
	return;
      }


      ItemType front() const { 
        if ( head == nullptr )
	   std::invalid_argument("Attempting to call front() on an empty list.");

        return head->data; 
      }
      ItemType back() const { 
        if ( head == nullptr )
	   std::invalid_argument("Attempting to call back() on an empty list.");

        return tail->data; 
      }

      // Auxiliary function swap 
      void swap( list<ItemType>& other ){
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(num_items, other.num_items);
	return;
      }


  }; // end of list<ItemType> interface


  // Specializations of the templated c++ swap function
  template <typename ItemType>
  inline void swap( list<ItemType>& x, list<ItemType>& y ){
    x.swap(y);
    return;
  }


}// end of Pic10B namespace


#endif
