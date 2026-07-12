#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <unordered_map>
#include <iostream>
#include <stdexcept>

// Generic LRU (Least Recently Used) Cache
// Backed by a HashMap (O(1) lookup) + Doubly Linked List (O(1) reorder/evict)
template <typename K, typename V>
class LRUCache {
private:
    struct Node {
        K key;
        V value;
        Node* prev;
        Node* next;
        Node(const K& k, const V& v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    Node* head;   // dummy head -> head->next is Most Recently Used
    Node* tail;   // dummy tail -> tail->prev is Least Recently Used
    std::unordered_map<K, Node*> cacheMap;

    // detach a node from the list
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // insert a node right after head (marks it as most recently used)
    void insertAtFront(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

public:
    explicit LRUCache(int cap) : capacity(cap) {
        if (cap <= 0) throw std::invalid_argument("Cache capacity must be > 0");
        head = new Node(K(), V());
        tail = new Node(K(), V());
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    // Non-copyable to avoid double-free of the linked list
    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(const LRUCache&) = delete;

    // Returns true and fills 'value' if key exists; marks it as most recently used
    bool get(const K& key, V& value) {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end()) return false;
        Node* node = it->second;
        value = node->value;
        removeNode(node);
        insertAtFront(node);
        return true;
    }

    // Insert or update a key. Evicts LRU entry if capacity is exceeded.
    void put(const K& key, const V& value) {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            Node* node = it->second;
            node->value = value;
            removeNode(node);
            insertAtFront(node);
            return;
        }

        if (static_cast<int>(cacheMap.size()) >= capacity) {
            Node* lru = tail->prev;
            std::cout << "[Evicted] Key: " << lru->key << " removed (capacity reached)\n";
            removeNode(lru);
            cacheMap.erase(lru->key);
            delete lru;
        }

        Node* newNode = new Node(key, value);
        insertAtFront(newNode);
        cacheMap[key] = newNode;
    }

    // Explicitly remove a key (no-op if absent)
    void remove(const K& key) {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end()) return;
        Node* node = it->second;
        removeNode(node);
        cacheMap.erase(it);
        delete node;
    }

    bool contains(const K& key) const {
        return cacheMap.find(key) != cacheMap.end();
    }

    int size() const { return static_cast<int>(cacheMap.size()); }
    int getCapacity() const { return capacity; }
    bool empty() const { return cacheMap.empty(); }

    // Prints current contents ordered Most-Recently-Used -> Least-Recently-Used
    void display() const {
        std::cout << "Cache [size " << size() << "/" << capacity << "] (MRU -> LRU): ";
        if (empty()) {
            std::cout << "(empty)\n";
            return;
        }
        Node* curr = head->next;
        bool first = true;
        while (curr != tail) {
            if (!first) std::cout << " -> ";
            std::cout << "{" << curr->key << ":" << curr->value << "}";
            first = false;
            curr = curr->next;
        }
        std::cout << "\n";
    }
};

#endif // LRU_CACHE_H
