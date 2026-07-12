#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include "../include/LRUCache.h"

using namespace std;

void printMenu() {
    cout << "\n===== Advanced LRU Cache Simulator =====\n";
    cout << "1. Put (insert/update key-value)\n";
    cout << "2. Get (fetch value by key)\n";
    cout << "3. Remove key\n";
    cout << "4. Display cache\n";
    cout << "5. Check if key exists\n";
    cout << "6. Show size/capacity\n";
    cout << "7. Run demo sequence\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

void runDemo(LRUCache<int, string>& cache) {
    cout << "\n--- Running demo sequence on capacity " << cache.getCapacity() << " cache ---\n";
    cache.put(1, "A");
    cache.display();
    cache.put(2, "B");
    cache.display();
    cache.put(3, "C");
    cache.display();

    string val;
    if (cache.get(1, val))
        cout << "Accessed key 1 -> " << val << " (now most recently used)\n";
    cache.display();

    cache.put(4, "D"); // should evict least recently used
    cache.display();

    cout << "--- Demo complete ---\n";
}

int main() {
    int capacity;
    cout << "Enter cache capacity: ";
    while (!(cin >> capacity) || capacity <= 0) {
        cout << "Please enter a positive integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    LRUCache<int, string> cache(capacity);
    int choice;

    do {
        printMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, try again.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int key; string value;
                cout << "Enter integer key: ";
                cin >> key;
                cout << "Enter string value: ";
                cin >> value;
                cache.put(key, value);
                cache.display();
                break;
            }
            case 2: {
                int key; string value;
                cout << "Enter key to fetch: ";
                cin >> key;
                if (cache.get(key, value))
                    cout << "Found -> " << value << "\n";
                else
                    cout << "Key not found in cache.\n";
                cache.display();
                break;
            }
            case 3: {
                int key;
                cout << "Enter key to remove: ";
                cin >> key;
                cache.remove(key);
                cache.display();
                break;
            }
            case 4:
                cache.display();
                break;
            case 5: {
                int key;
                cout << "Enter key to check: ";
                cin >> key;
                cout << (cache.contains(key) ? "Present\n" : "Not present\n");
                break;
            }
            case 6:
                cout << "Size: " << cache.size() << " / Capacity: " << cache.getCapacity() << "\n";
                break;
            case 7:
                runDemo(cache);
                break;
            case 0:
                cout << "Exiting. Goodbye!\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
