#ifndef __NESTED_DL_CONST_ITERATOR_H__
#define __NESTED_DL_CONST_ITERATOR_H__

// This is a nested class of Pic10B::list<T>
class const_iterator{
  // Let the parent class have access to all fields and functions
  friend class list<ItemType>;

  private: 
    // class fields 
    list<ItemType>* parent;  // The list that the const_iterator belongs to
    typename list<ItemType>::NestedNode* current_node;

    // The constructor here is private. However, the parent 
    // class has access to it. This is the standard behavior
    // for const_iterators.
    const_iterator(list<ItemType>* theParent, NestedNode* thePosition) :
        parent(theParent), current_node(thePosition) {} 

  public:
    // Copy constructor (PUBLIC). Other classes may make a copy. 
    const_iterator( const const_iterator& source ) :
      parent(source.parent), current_node(source.current_node) {}

    // REQUIRED. Dereference operator (rvalue). See also iterator 
    const ItemType& operator*() const { 
      if ( current_node == nullptr )
        throw std::invalid_argument("Attempting to dereference end()");
      return current_node->data;
    }

    // REQUIRED. operator++ (prefix version)
    const_iterator& operator++(){
      if ( current_node == nullptr )
        throw std::invalid_argument("Attempting to advance past end()");
      current_node = current_node->next;
      return *this;
    }

    // REQUIRED. operator++ (postfix version)
    const_iterator operator++(int unused){
      const_iterator toBeReturned = *this;  // saves the current position 
      ++(*this);  // avoids repetition of code [ and also checks for valid range ]
      return toBeReturned;
    }

    // REQUIRED. operator-- (prefix version)
    const_iterator& operator--(){
      if ( current_node == parent->head )
        throw std::invalid_argument("Attempting to move before begin()");
      if ( current_node == nullptr )  // one node past the last node?
        current_node = parent->tail;  // come back to the tail
      else
        current_node = current_node->prev;
      return *this;
    }

    // REQUIRED. operator-- (postfix version)
    const_iterator operator--(int unused){
      const_iterator toBeReturned = *this;  // See postfix operator++ (above)
      --(*this);
      return toBeReturned;
    }

    // NOT REQUIRED. Dereference companion ( operator-> ). Only works 
    // if ItemType is a class [or struct].
    const ItemType* operator->() const {
      if ( current_node == nullptr )
        throw std::invalid_argument("Attempting to dereference end()");
      return &(current_node->data);
    }

    // NOT REQUIRED. Boolean == and !=
    bool operator==( const const_iterator& rhs ) const {
      return current_node == rhs.current_node;
    }
    bool operator!=( const const_iterator& rhs ) const {
      return !operator==(rhs); 
    }

};

#endif
