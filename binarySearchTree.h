#ifndef SEARCH_H
#define SEARCH_H
#include "binaryTree.h"

template <class elemType>
class binarySearchTree : public binaryTreeType<elemType>
{
public:
  bool search(const elemType &searchItem) const;
  void insert(const elemType &insertItem);
  void deleteNode(const elemType &deleteItem);

private:
  void search(const elemType &searchItem, bool &found, nodeType<elemType> *&current) const;
  void insert(const elemType &insertItem, nodeType<elemType> *&current);
  void deleteFromTree(nodeType<elemType> *&p);
};

template <class elemType>
bool binarySearchTree<elemType>::search(const elemType &searchItem) const
{
  nodeType<elemType> *current;
  bool found = false;
  search(searchItem, found, current);
  return found;
}

template <class elemType>
void binarySearchTree<elemType>::search(const elemType &searchItem, bool &found, nodeType<elemType> *&current) const
{
  current = this->root;
  found = false;
  while (current != nullptr && !found)
  {
    if (current->info == searchItem)
      found = true;
    else if (current->info > searchItem)
      current = current->lLink;
    else
      current = current->rLink;
  }
}

template <class elemType>
void binarySearchTree<elemType>::insert(const elemType &insertItem)
{
  insert(insertItem, this->root);
}

template <class elemType>
void binarySearchTree<elemType>::insert(const elemType &insertItem, nodeType<elemType> *&current)
{
  if (current == nullptr)
  {
    current = new nodeType<elemType>;
    current->info = insertItem;
    current->lLink = nullptr;
    current->rLink = nullptr;
  }
  else if (current->info > insertItem)
    insert(insertItem, current->lLink);
  else
    insert(insertItem, current->rLink);
}

template <class elemType>
void binarySearchTree<elemType>::deleteNode(const elemType &deleteItem)
{
  nodeType<elemType> *current;
  nodeType<elemType> *trailCurrent;
  bool found = false;
  if (this->root == nullptr)
    std::cout << "Cannot delete from an empty tree." << std::endl;
  else
  {
    current = this->root;
    trailCurrent = this->root;
    while (current != nullptr && !found)
    {
      if (current->info == deleteItem)
        found = true;
      else
      {
        trailCurrent = current;
        if (current->info > deleteItem)
          current = current->lLink;
        else
          current = current->rLink;
      }
    }
    if (current == nullptr)
      std::cout << "The delete item is not in the tree." << std::endl;
    else if (found)
    {
      if (current == this->root)
        deleteFromTree(this->root);
      else if (trailCurrent->info > deleteItem)
        deleteFromTree(trailCurrent->lLink);
      else
        deleteFromTree(trailCurrent->rLink);
    }
    else
      std::cout << "The delete item is not in the tree." << std::endl;
  }
}

template <class elemType>
void binarySearchTree<elemType>::deleteFromTree(nodeType<elemType> *&p)
{
  nodeType<elemType> *current;
  nodeType<elemType> *trailCurrent;
  nodeType<elemType> *temp;
  if (p == nullptr)
    std::cout << "Error: The node to be deleted is NULL." << std::endl;
  else if (p->lLink == nullptr && p->rLink == nullptr)
  {
    temp = p;
    p = nullptr;
    delete temp;
  }
  else if (p->lLink == nullptr)
  {
    temp = p;
    p = temp->rLink;
    delete temp;
  }
  else if (p->rLink == nullptr)
  {
    temp = p;
    p = temp->lLink;
    delete temp;
  }
  else
  {
    current = p->lLink;
    trailCurrent = nullptr;
    while (current->rLink != nullptr)
    {
      trailCurrent = current;
      current = current->rLink;
    }
    p->info = current->info;
    if (trailCurrent == nullptr)
      p->lLink = current->lLink;
    else
      trailCurrent->rLink = current->lLink;
    delete current;
  }
}

#endif