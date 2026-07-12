# Advanced LRU Cache Simulator

A C++ project implementing an optimized LRU (Least Recently Used) Cache using HashMap and Doubly Linked List.

## Features

- O(1) insertion and retrieval
- Cache eviction mechanism
- Efficient memory management
- Object-oriented implementation

## Tech Stack

- C++
- Data Structures & Algorithms
- HashMap
- Doubly Linked List

## Concepts Used

- LRU Cache
- Dynamic Memory Handling
- OOP
- Optimization Techniques

## Project Structure

```
advanced-lru-cache-simulator/
├── include/
│   └── LRUCache.h      # Templated LRU Cache (HashMap + Doubly Linked List)
├── src/
│   └── main.cpp        # Interactive console simulator
├── Makefile            # Build configuration
├── .gitignore
└── README.md
```

## How It Works

The cache is built with two data structures working together for O(1) operations:

- **`unordered_map<K, Node*>`** — gives instant O(1) lookup of any key.
- **Doubly linked list** — keeps track of usage order. The most recently
  used item sits right after the head, and the least recently used item
  sits right before the tail, so eviction is also O(1).

On every `get`/`put`, the accessed node is unlinked and moved to the front
of the list. When the cache exceeds capacity, the node just before the
tail (the LRU node) is evicted.

## Build & Run

You need a C++17-compatible compiler (g++/clang++).

```bash
# Build
make

# Run
./lru_cache_simulator
# or
make run

# Clean build artifacts
make clean
```

### Manual compile (without Makefile)

```bash
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude src/main.cpp -o lru_cache_simulator
./lru_cache_simulator
```

## Usage

On launch you'll be asked for a cache capacity, then presented with a menu:

```
1. Put (insert/update key-value)
2. Get (fetch value by key)
3. Remove key
4. Display cache
5. Check if key exists
6. Show size/capacity
7. Run demo sequence
0. Exit
```

Option **7** runs a scripted demo so you can see insertion, access-based
reordering, and eviction happen automatically without typing input manually.

### Example demo output (capacity 3)

```
Cache [size 1/3] (MRU -> LRU): {1:A}
Cache [size 2/3] (MRU -> LRU): {2:B} -> {1:A}
Cache [size 3/3] (MRU -> LRU): {3:C} -> {2:B} -> {1:A}
Accessed key 1 -> A (now most recently used)
Cache [size 3/3] (MRU -> LRU): {1:A} -> {3:C} -> {2:B}
[Evicted] Key: 2 removed (capacity reached)
Cache [size 3/3] (MRU -> LRU): {4:D} -> {1:A} -> {3:C}
```

## Future Improvements

- Add unit tests (e.g. with GoogleTest)
- Support TTL (time-to-live) based expiry
- Thread-safety for concurrent access
- CLI flags to run non-interactively for scripting/benchmarking

## Author

Pawan Pandey ([@pawanpandit1](https://github.com/pawanpandit1))
