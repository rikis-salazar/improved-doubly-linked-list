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
      #include "nested_iterator.h"
      // and make it a friend...
      friend class iterator;

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


      /** Some other basic functions that DO NOT need iterators */
      ItemType& front(){ 
        if ( head == nullptr )
	   std::invalid_argument("Attempting to call front() on an empty list.");
        return head->data; 
      }

      const ItemType& front() const { 
        if ( head == nullptr )
	   std::invalid_argument("Attempting to call front() on an empty list.");
        return head->data; 
      }

      ItemType& back(){ 
        if ( tail == nullptr )
	   std::invalid_argument("Attempting to call back() on an empty list.");
        return tail->data; 
      }

      const ItemType& back() const { 
        if ( tail == nullptr )
	   std::invalid_argument("Attempting to call back() on an empty list.");
        return tail->data; 
      }

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

      void pop_front(){
        if ( head == nullptr )
	   std::invalid_argument("Attempting to call pop_front() on an empty list.");
	NestedNode* toBeDeleted = head;
	head = head->next;
	delete toBeDeleted;
	num_items--;
	if ( head != nullptr )
	  head->prev = nullptr;
	else
	  tail = nullptr;
        return;
      }

      void pop_back(){
        if ( tail == nullptr )
	   std::invalid_argument("Attempting to call pop_back() on an empty list.");
	NestedNode* toBeDeleted = tail;
	tail = tail->prev;
	delete toBeDeleted;
	num_items--;
	if ( tail != nullptr )
	  tail->next = nullptr;
	else
	  head = nullptr;
        return;
      }


      /** Auxiliary functions */
      // Member function swap called by operator=
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
