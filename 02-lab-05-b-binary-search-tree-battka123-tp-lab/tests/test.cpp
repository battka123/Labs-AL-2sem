// Copyright 2023 Ivan <i.suschin@yandex.ru>

#include <gtest/gtest.h>

#include "binarytree.hpp"

TEST(BinarySearchTreeTest, AddAndFindNodes) {
  BinarySearchTree<int> bst;

  bst.Add(5);
  bst.Add(3);
  bst.Add(7);
  bst.Add(1);
  bst.Add(9);
  bst.Add(4);
  bst.Add(6);
  bst.Add(8);

  EXPECT_EQ(bst.Find(5)->Value, 5);
  EXPECT_EQ(bst.Find(3)->Value, 3);
  EXPECT_EQ(bst.Find(7)->Value, 7);
  EXPECT_EQ(bst.Find(1)->Value, 1);
  EXPECT_EQ(bst.Find(9)->Value, 9);
  EXPECT_EQ(bst.Find(4)->Value, 4);
  EXPECT_EQ(bst.Find(6)->Value, 6);
  EXPECT_EQ(bst.Find(8)->Value, 8);
}

TEST(BinarySearchTreeTest, RemoveNodes) {
  BinarySearchTree<int> bst;

  bst.Add(5);
  bst.Add(3);
  bst.Add(7);
  bst.Add(1);
  bst.Add(9);
  bst.Add(4);
  bst.Add(6);
  bst.Add(8);

  BinarySearchTree<int>::Node* nodeToRemove = bst.Find(5);
  bst.Remove(nodeToRemove);
  EXPECT_EQ(bst.Find(5), nullptr);
  EXPECT_EQ(bst.Find(3)->Value, 3);
  EXPECT_EQ(bst.Find(7)->Value, 7);
  EXPECT_EQ(bst.Find(1)->Value, 1);
  EXPECT_EQ(bst.Find(9)->Value, 9);
  EXPECT_EQ(bst.Find(4)->Value, 4);
  EXPECT_EQ(bst.Find(6)->Value, 6);
  EXPECT_EQ(bst.Find(8)->Value, 8);

  nodeToRemove = bst.Find(3);
  bst.Remove(nodeToRemove);
  EXPECT_EQ(bst.Find(5), nullptr);
  EXPECT_EQ(bst.Find(3), nullptr);
  EXPECT_EQ(bst.Find(7)->Value, 7);
  EXPECT_EQ(bst.Find(1)->Value, 1);
  EXPECT_EQ(bst.Find(9)->Value, 9);
  EXPECT_EQ(bst.Find(4)->Value, 4);
  EXPECT_EQ(bst.Find(6)->Value, 6);
  EXPECT_EQ(bst.Find(8)->Value, 8);

  nodeToRemove = bst.Find(7);
  bst.Remove(nodeToRemove);
  EXPECT_EQ(bst.Find(5), nullptr);
  EXPECT_EQ(bst.Find(3), nullptr);
  EXPECT_EQ(bst.Find(7), nullptr);
  EXPECT_EQ(bst.Find(1)->Value, 1);
  EXPECT_EQ(bst.Find(9)->Value, 9);
  EXPECT_EQ(bst.Find(4)->Value, 4);
  EXPECT_EQ(bst.Find(6)->Value, 6);
  EXPECT_EQ(bst.Find(8)->Value, 8);

  nodeToRemove = bst.Find(1);
  bst.Remove(nodeToRemove);
  EXPECT_EQ(bst.Find(5), nullptr);
  EXPECT_EQ(bst.Find(3), nullptr);
  EXPECT_EQ(bst.Find(7), nullptr);
  EXPECT_EQ(bst.Find(1), nullptr);
  EXPECT_EQ(bst.Find(9)->Value, 9);
  EXPECT_EQ(bst.Find(4)->Value, 4);
  EXPECT_EQ(bst.Find(6)->Value, 6);
  EXPECT_EQ(bst.Find(8)->Value, 8);

  nodeToRemove = bst.Find(9);
  bst.Remove(nodeToRemove);
  EXPECT_EQ(bst.Find(5), nullptr);
  EXPECT_EQ(bst.Find(3), nullptr);
  EXPECT_EQ(bst.Find(7), nullptr);
  EXPECT_EQ(bst.Find(1), nullptr);
  EXPECT_EQ(bst.Find(9), nullptr);
  EXPECT_EQ(bst.Find(4)->Value, 4);
  EXPECT_EQ(bst.Find(6)->Value, 6);
  EXPECT_EQ(bst.Find(8)->Value, 8);

  nodeToRemove = bst.Find(4);
  bst.Remove(nodeToRemove);
  EXPECT_EQ(bst.Find(5), nullptr);
  EXPECT_EQ(bst.Find(3), nullptr);
  EXPECT_EQ(bst.Find(7), nullptr);
  EXPECT_EQ(bst.Find(1), nullptr);
  EXPECT_EQ(bst.Find(9), nullptr);
  EXPECT_EQ(bst.Find(4), nullptr);
  EXPECT_EQ(bst.Find(6)->Value, 6);
  EXPECT_EQ(bst.Find(8)->Value, 8);

  nodeToRemove = bst.Find(6);
  bst.Remove(nodeToRemove);
  EXPECT_EQ(bst.Find(5), nullptr);
  EXPECT_EQ(bst.Find(3), nullptr);
  EXPECT_EQ(bst.Find(7), nullptr);
  EXPECT_EQ(bst.Find(1), nullptr);
  EXPECT_EQ(bst.Find(9), nullptr);
  EXPECT_EQ(bst.Find(4), nullptr);
  EXPECT_EQ(bst.Find(6), nullptr);
  EXPECT_EQ(bst.Find(8)->Value, 8);

  nodeToRemove = bst.Find(8);
  bst.Remove(nodeToRemove);
  EXPECT_EQ(bst.Find(5), nullptr);
  EXPECT_EQ(bst.Find(3), nullptr);
  EXPECT_EQ(bst.Find(7), nullptr);
  EXPECT_EQ(bst.Find(1), nullptr);
  EXPECT_EQ(bst.Find(9), nullptr);
  EXPECT_EQ(bst.Find(4), nullptr);
  EXPECT_EQ(bst.Find(6), nullptr);
  EXPECT_EQ(bst.Find(8), nullptr);
}

TEST(BinarySearchTreeTest, DeleteEmptyTree) {
  BinarySearchTree<int>* emptyTree = new BinarySearchTree<int>();
  delete emptyTree;
}

TEST(BinarySearchTreeTest, PrintByLevelsTest) {
  BinarySearchTree<int> bst;
  bst.Add(5);
  bst.Add(3);
  bst.Add(7);
  bst.Add(1);
  bst.Add(4);
  bst.Add(6);
  bst.Add(8);

  std::stringstream ss;
  ss << bst;

  std::string expected = "5 \n3 7 \n1 4 6 8 \n";
  EXPECT_EQ(ss.str(), expected);
}

TEST(BinarySearchTreeTest, DepthTest) {
  BinarySearchTree<int> bst;
  EXPECT_EQ(bst.Depth(), 0);

  bst.Add(5);
  EXPECT_EQ(bst.Depth(), 1);

  bst.Add(3);
  bst.Add(7);
  EXPECT_EQ(bst.Depth(), 2);

  bst.Add(1);
  bst.Add(4);
  bst.Add(6);
  bst.Add(8);
  EXPECT_EQ(bst.Depth(), 3);
}

TEST(BinarySearchTreeTest, IsBinarySearchTreeTest) {
  BinarySearchTree<int> tree;
  tree.Add(7);
  tree.Add(6);
  tree.Add(3);
  tree.Add(8);
  tree.Add(1);
  tree.Add(2);
  tree.Add(4);
  BinarySearchTree<int>::Node* root = tree.Find(7);
  bool result = tree.IsBinarySearchTree(root);
  EXPECT_TRUE(result);
}
