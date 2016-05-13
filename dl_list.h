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
      // Nested 'iterator' class (see nested_iterator.h)
      #include "nested_iterator.h"
      // and make it a friend...
      friend class iterator;

      // Nested 'const iterator' class (see nested_const_iterator.h)
      #include "nested_const_iterator.h"
      // Make it a friend...
      friend class const_iterator;

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

      // Copy constructor (see functions that use iterators below)
      // list( const list<ItemType>& source ); 

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
      bool empty() const {
        return ( head == nullptr );
      }

      std::size_t size() const {
        return num_items;
      }

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


      /** Functions that use iterators or const_iterators */
      iterator begin(){
        return iterator(this, head);
      }

      const_iterator begin() const {
        return const_iterator(this, head);
      }

      iterator end(){
        return iterator(this, nullptr);
      }

      const_iterator end() const {
        return const_iterator(this, nullptr);
      }

      // Copy constructor
      list( const list<ItemType>& source ){
        head = tail = nullptr;  // all constructors should properly 
	num_items = 0;          // initialize all fields
        for ( const_iterator iter = source.begin() ; iter != source.end() ; ++iter )
	  push_back(*iter);
      } 

      iterator insert(iterator position, const ItemType& theData){
        // Check for special cases
	if ( position == head ){  // insert new head?
	  push_front(theData);
	  return begin();
	}
	else if( position.current_node == nullptr ) { // new tail?
	  push_back(theData);
	  return iterator(this, tail);
	}
	// In both cases abovem num_items is updated via push_XXX
	else{ // Ok then. Inserting in the middle of the list.
	  NestedNode* newNode = new NestedNode( theData, 
	      position.current_node->prev, position.current_node);
	  position.current_node->prev->next = newNode;
	  position.current_node->prev = newNode;
	  num_items++;
	  return iterator(this, newNode);
	}
      }

      iterator erase(iterator position){
        if ( empty() )
	  throw std::invalid_argument("Attempting to erase from an empty list");
	if ( position == end() )
	  throw std::invalid_argument("Attempting to erase past the last node");
	// create return value: iterator that references the next node
	iterator toBeReturned = position;
	++toBeReturned;
	// Special cases? begin(), end()
	if ( position.current_node == head )
	  pop_front();
	else if ( position.current_node == tail )
	  pop_back();
	else{
	  // Create a local NestedNode that we'll use to call delete
	  // Since this local node will be destroyed at the end of 
	  // this else block, it will not become a dangling pointer
	  NestedNode* toBeDeleted = position.current_node;
	  toBeDeleted->prev->next = toBeDeleted->next;
	  toBeDeleted->next->prev = toBeDeleted->prev;
	  delete toBeDeleted;
	}
	return toBeReturned;
      }

      void remove( const ItemType& theData ){
        for ( iterator iter = begin() ; iter != end() ; ++iter ){
	  if ( *iter == theData )
	     erase(iter);
	}
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
