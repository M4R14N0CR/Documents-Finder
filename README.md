<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
  <h1>Document and Cache Management System in C</h1>

  <h2>Overview</h2>
  <p>
    This project implements several data structures and functions in C to index, search, and manage documents.
    It combines singly linked lists, binary trees (with splay tree operations), and hash tables to build a system
    that reads files from a directory, searches for specific words or phrases, and manages a cache on disk.
  </p>

  <h2>Main Features</h2>
  <ul>
    <li>
      <strong>Linked Lists:</strong> Implements simple linked lists to manage textual data, enabling operations such as insertion and printing.
    </li>
    <li>
      <strong>Binary Trees and Splay Operations:</strong> Provides a binary search tree with splay tree functionality for efficient dynamic access and cache management.
    </li>
    <li>
      <strong>Hash Tables:</strong> Uses a hash table to index documents by file name. It supports dynamic resizing when occupancy reaches 75% to maintain efficiency.
    </li>
    <li>
      <strong>File I/O and Directory Traversal:</strong> Reads files from a designated directory ("test"), stores the content in the hash table, and enables search operations.
    </li>
    <li>
      <strong>Search Functionality:</strong> Allows searching for a specific word or phrase within the document contents, as well as searching for documents by file name.
    </li>
    <li>
      <strong>Cache Management:</strong> Implements functions to save and load a cache (using a splay tree) to and from disk, ensuring faster future retrievals.
    </li>
    <li>
      <strong>Interactive Menu:</strong> Provides a console menu for users to choose among different operations like searching, displaying documents, and viewing cache content.
    </li>
  </ul>

  <h2>Data Structures and Algorithms</h2>
  <ul>
    <li>
      <em>Singly Linked List:</em> Stores text strings for document details or search results.
    </li>
    <li>
      <em>Hash Table:</em> Uses a hash function based on character values and linear probing to resolve collisions. It resizes automatically when needed.
    </li>
    <li>
      <em>Binary Tree with Splay Operations:</em> Supports quick access and dynamic reordering of cached search results.
    </li>
    <li>
      <em>File Reading Functions:</em> Reads file contents into a single character array, enabling full-text search.
    </li>
  </ul>

  <h2>Conclusion</h2>
  <p>
    Overall, this project demonstrates efficient document management and caching by integrating various dynamic data structures in C.
    It reads and indexes documents from a directory, provides comprehensive search capabilities, and manages a cache to optimize repeated queries.
    This system is an effective example of combining low-level file operations with advanced data structure management for practical applications.
  </p>
</body>
</html>
