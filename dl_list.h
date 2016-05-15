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
      // Nested friend 'iterator' class (see nested_iterator.h)
      #include "nested_iterator.h"
      friend class iterator;

      // Nested friend 'const iterator' class (see nested_const_iterator.h)
      #include "nested_const_iterator.h"
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

      // Copy constructor 
      // See definition below in the functions-that-use-iterators section

      // Destructor
      // Note that repeatedly calling pop_back() [or pop_front()]
      // also destroys the list, but the function below is 
      // more efficient. Why???  (Hint: If num_items is excluded 
      // from this class, both approaches are equivalent)
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
      // #ThisIsNotHowWeLearnedItInClass 
      // #EasterEgg



      /** SECTION: [basic-]functions-that-DO-NOT-need-iterators */
      bool empty() const {
        return ( head == nullptr );
      }

      std::size_t size() const {
        return num_items;
      }

      ItemType& front(){ 
        if ( head == nullptr )
	   throw std::invalid_argument("Attempting to call front() on an empty list.");
        return head->data; 
      }

      const ItemType& front() const { 
        if ( head == nullptr )
	   throw std::invalid_argument("Attempting to call front() on an empty list.");
        return head->data; 
      }

      ItemType& back(){ 
        if ( tail == nullptr )
	   throw std::invalid_argument("Attempting to call back() on an empty list.");
        return tail->data; 
      }

      const ItemType& back() const { 
        if ( tail == nullptr )
	   throw std::invalid_argument("Attempting to call back() on an empty list.");
        return tail->data; 
      }

      void push_front( const ItemType& theData ){
        // Recall that the constructor for NestedNode performs
	// the linking. 
	//     NestedNode( theData , prevNode , nextNode )

	// Attach new node to list
        head = new NestedNode(theData, nullptr, head); 

	// If other nodes are present, have the head link to
	// this new node
	if ( head->next != nullptr ) 
	  head->next->prev = head;

	// If the list was empty, have tail point to this
	// new node as well
	if ( tail == nullptr )  
	  tail = head;

	// Update the number of items
	num_items++;

	return;
      }

      void push_back( const ItemType& theData ){
	// if there is at least one node rearrange links
	if ( tail != nullptr ){
	  tail->next =  new NestedNode(theData, tail, nullptr);
	  tail = tail->next;
	  num_items++;
	}
	// if not, the back and the front agree. Use push_front() instead
	else
	  push_front(theData);  //  numItems is increased here as well
	return;
      }

      void pop_front(){
        if ( head == nullptr )
	   throw std::invalid_argument("Attempting to call pop_front() on an empty list.");

	/** 
	   It is a safe practice to only release memory 
	   via a local pointer. Since this local pointer 
	   will be destroyed at the end of this function,
	   the chances of having a dangling pointer are 
	   reduced.
	*/
	// head survives this function, toBeDeleted does not. 
	NestedNode* toBeDeleted = head;  

	// Update head and release memory
	head = head->next;
	delete toBeDeleted; 

	// Update number of nodes
	num_items--;

	// If there is a new head, update its prev pointer.
	// If not, we have a new empty list. Update tail.
	if ( head != nullptr )
	  head->prev = nullptr;
	else
	  tail = nullptr;

        return;
      }

      void pop_back(){
        if ( tail == nullptr )
	   throw std::invalid_argument("Attempting to call pop_back() on an empty list.");

	// Local pointer (see pop_front() above)
	NestedNode* toBeDeleted = tail;

	// Rearrange links, release memory, update number 
	// of nodes and check for new status of the list
	tail = tail->prev;
	delete toBeDeleted;
	num_items--;

	if ( tail != nullptr )
	  tail->next = nullptr;
	else
	  head = nullptr;

        return;
      }



      /** SECTION: Functions-that-use-iterators [or const_iterators] */
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

	// A const_iterator is needed here! Why???
	// Uncomment the lines below and recompile to see what goes wrong
        // for ( iterator iter = source.begin() ; iter != source.end() ; ++iter )
	//   push_back(*iter);
	//
	// Hint: If we use the [unsafe] signature 
	//   list( list<ItemType>& source );
	// then an iterator works.

        for ( const_iterator iter = source.begin() ; iter != source.end() ; ++iter )
	  push_back(*iter);
      } 


      // insert returns an iterator that points to the location of
      // the new node
      iterator insert(iterator position, const ItemType& theData){
	// Note: In both special cases below num_items is updated via 
	// push_back() or push_front()
	if ( position.current_node == head ){  // inserting a new head?
	  push_front(theData);
	  return begin();
	}
	else if( position.current_node == nullptr ) { // or a new tail?
	  push_back(theData);
	  return iterator(this, tail);
	}
	// Ok then. We are inserting somewhere in the middle.
	// Rearrange links, and upate the number of nodes.
	else{ 
	  NestedNode* newNode = new NestedNode( theData, 
	      position.current_node->prev, position.current_node);
	  position.current_node->prev->next = newNode;
	  position.current_node->prev = newNode;
	  num_items++;
	  return iterator(this, newNode);
	}
      }


      // erase returns an iterator pointing at the node that is 
      // next to the node that will be erased
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
	  // Use local pointer to release memory
	  NestedNode* toBeDeleted = position.current_node;
	  toBeDeleted->prev->next = toBeDeleted->next;
	  toBeDeleted->next->prev = toBeDeleted->prev;
	  delete toBeDeleted;
	}
	return toBeReturned;
      }


      // remove erases all nodes matching the data passed as 
      // parameter
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


  // Specialization of the templated c++ swap function
  template <typename ItemType>
  inline void swap( list<ItemType>& x, list<ItemType>& y ){
    x.swap(y);
    return;
  }


}// end of Pic10B namespace


#endif
