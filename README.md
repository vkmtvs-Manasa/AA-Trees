# AA-Trees
# AA Trees in C++

## Overview

This project implements an **AA Tree**, a self-balancing Binary Search Tree (BST) that maintains efficient search, insertion, and deletion operations. AA Trees simplify the balancing logic of Red-Black Trees by using only two balancing operations: **Skew** and **Split**.

## Features

* Insert elements into the AA Tree
* Delete elements from the AA Tree
* Search for elements
* Maintain balanced tree structure automatically
* Inorder Traversal
* Efficient operations with O(log n) time complexity

## Data Structure

An AA Tree is a balanced BST where each node contains:

* Key value
* Level information
* Left child pointer
* Right child pointer

### Balancing Operations

#### Skew

Removes left horizontal links by performing a right rotation.

#### Split

Removes consecutive right horizontal links by performing a left rotation and increasing the level.

## Time Complexity

| Operation | Complexity |
| --------- | ---------- |
| Search    | O(log n)   |
| Insert    | O(log n)   |
| Delete    | O(log n)   |
| Traversal | O(n)       |

## Project Structure

```text
AA-Trees/
│
├── main.cpp
├── AATree.cpp
├── AATree.h
└── README.md
```

## Compilation and Execution

### Using g++

```bash
g++ main.cpp -o aatree
./aatree
```

## Sample Operations

```text
1. Insert
2. Delete
3. Search
4. Display Inorder
5. Exit
```

## Applications

* Database indexing
* Memory management systems
* Symbol tables
* Dictionary implementations
* Ordered data storage

## Learning Outcomes

Through this project, I gained practical experience with:

* Self-balancing Binary Search Trees
* Tree rotations
* Dynamic memory management in C++
* Efficient data structure implementation
* Algorithm analysis and optimization


