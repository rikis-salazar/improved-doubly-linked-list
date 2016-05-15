#ifndef __NESTED_DL_NODE_H__
#define __NESTED_DL_NODE_H__

// This is a nested class of Pic10B::list<T>
class NestedNode{
  
  friend class list<ItemType>;

  private:
    ItemType data;
    NestedNode* prev;
    NestedNode* next;

  public:
    // We let this class handle the linking of next and prev
    NestedNode(const ItemType& theData, NestedNode* p = nullptr, 
               NestedNode* n = nullptr ) : 
      data(theData), prev(p), next(n) {}
};

#endif
