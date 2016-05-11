#ifndef __NESTED_DL_ITERATOR_H__
#define __NESTED_DL_ITERATOR_H__

// This is a nested class of Pic10B::list<T>
class iterator{
  // Let the parent class have access to all fields and functions
  friend class list<ItemType>;

  private: 
    // class fields 
    list<ItemType>* parent;  // The list that the iterator belongs to
    typename list<ItemType>::NestedNode* current_node;

    // The constructor here is private. However, the parent 
    // class has access to it. This is the standard behavior
    // for iterators.
    iterator(list<ItemType>* theParent, NestedNode* thePosition) :
        parent(theParent), current_node(thePosition) {} 

  public:
    // Dereference operator, returns by reference.
    ItemType& operator*() const { 
      if ( current_node == nullptr )
        std::invalid_argument("Attempting to dereference end()");
      return current_node->data;
    }

    // Dereference companion ( operator-> ). Only works if ItemType
    // is a class [ or a struct ].
    ItemType* operator->() const {
      if ( current_node == nullptr )
        std::invalid_argument("Attempting to dereference end()");
      return &(current_node->data);
    }

};

#endif
