# FLAM
Flam OpenGL

This repository contains three different projects

1.LRU Cache

->Uses a doubly linked list and an unordered_map.

->Ensures O(1) complexity for get() and put() operations.

->The head of the list stores the most recently used item, and the tail stores the least recently used.

2.Hashmap 

->Implements a hash function: key % size.

->Uses separate chaining with a vector of buckets (each a list of key-value pairs).

->put(key, value): Add or update entry.

->get(key): Retrieve value by key.

->remove(key): Delete entry by key.

3.Mini Solar System OpenGL

->Sun stays centered and glows using a custom GLSL shader.

->Planets orbit the Sun and rotate on their own axes.

->One planet has a moon orbiting it, demonstrating hierarchical transformations.

->Mouse drag or touch rotates the camera view
