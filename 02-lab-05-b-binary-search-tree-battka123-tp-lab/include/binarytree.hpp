// Copyright 2023 Ivan <i.suschin@yandex.ru>

#ifndef INCLUDE_BINARYTREE_HPP_
#define INCLUDE_BINARYTREE_HPP_

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>

template <class T>
class BinarySearchTree {
 public:
  struct Node {
    Node* Parent;
    Node* Left;
    Node* Right;
    T Value;
    explicit Node(const T& value)
        : Left(nullptr), Right(nullptr), Value(value) {}
    Node(Node* parent, Node* left, Node* right, T value)
        : Parent(parent), Left(left), Right(right), Value(value) {}
  };

  BinarySearchTree() : root(nullptr) {}
  ~BinarySearchTree() { deleteTree(root); }

  void Add(const T& value) { root = addNode(root, value); }
  Node* Find(const T& value) { return findNode(root, value); }
  void Remove(Node* node) { root = removeNode(root, node); }

  [[nodiscard]] unsigned int Depth() const { return DepthHelper(root); }

  bool IsBinarySearchTree(BinarySearchTree<T>::Node* Root) {
    if (Root == nullptr) {
      return true;
    }
    return IsBSTHelper(Root, std::numeric_limits<T>::min(),
                       std::numeric_limits<T>::max());
  }

  bool IsBSTHelper(BinarySearchTree<T>::Node* node, T min_value, T max_value) {
    if (node == nullptr) {
      return true;
    }
    if (node->Value < min_value || node->Value > max_value) {
      return false;
    }
    return IsBSTHelper(node->Left, min_value, node->Value) &&
           IsBSTHelper(node->Right, node->Value, max_value);
  }

 private:
  Node* root;

  Node* addNode(Node* node, const T& value) {
    if (node == nullptr) {
      return new Node(value);
    }
    if (value < node->Value) {
      node->Left = addNode(node->Left, value);
    } else if (value > node->Value) {
      node->Right = addNode(node->Right, value);
    }
    return node;
  }

  Node* findNode(Node* node, const T& value) {
    if (node == nullptr || node->Value == value) {
      return node;
    }
    if (value < node->Value) {
      return findNode(node->Left, value);
    } else {
      return findNode(node->Right, value);
    }
  }

  Node* removeNode(Node* node, Node* toRemove) {
    if (node == nullptr) {
      return nullptr;
    }
    if (toRemove->Value < node->Value) {
      node->Left = removeNode(node->Left, toRemove);
    } else if (toRemove->Value > node->Value) {
      node->Right = removeNode(node->Right, toRemove);
    } else {
      if (node->Left == nullptr) {
        Node* rightChild = node->Right;
        delete node;
        return rightChild;
      } else if (node->Right == nullptr) {
        Node* leftChild = node->Left;
        delete node;
        return leftChild;
      } else {
        Node* minRightNode = findMinNode(node->Right);
        node->Value = minRightNode->Value;
        node->Right = removeNode(node->Right, minRightNode);
      }
    }
    return node;
  }

  Node* findMinNode(Node* node) {
    while (node->Left != nullptr) {
      node = node->Left;
    }
    return node;
  }

  void deleteTree(Node* node) {
    if (node != nullptr) {
      deleteTree(node->Left);
      deleteTree(node->Right);
      delete node;
    }
  }

  friend std::ostream& operator<<(std::ostream& out,
                                  const BinarySearchTree<T>& bst) {
    if (bst.root == nullptr) {
      return out;
    }
    std::queue<Node*> q;
    q.push(bst.root);
    while (!q.empty()) {
      int size = q.size();
      for (int i = 0; i < size; i++) {
        Node* curr = q.front();
        q.pop();
        out << curr->Value << " ";
        if (curr->Left != nullptr) {
          q.push(curr->Left);
        }
        if (curr->Right != nullptr) {
          q.push(curr->Right);
        }
      }
      out << std::endl;
    }
    return out;
  }

  static unsigned int DepthHelper(Node* node) {
    if (node == nullptr) {
      return 0;
    }
    unsigned int Left_Depth = DepthHelper(node->Left);
    unsigned int Right_Depth = DepthHelper(node->Right);
    return 1 + std::max(Left_Depth, Right_Depth);
  }
};

#endif // INCLUDE_BINARYTREE_HPP_
