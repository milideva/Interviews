/*
    Map (collections of {key, value} pairs)
    - map[key] = value
    - Ordered by the keys. Implemented using a BST (RBTree)
    - Use unordered_map for a hashtable of key value pairs
    - No duplicates - use multimap for duplicates
    - Value can be updated for a given key
    - map/unordered_map/multimap 3 options

    Typical Operations
    insert(newKV) returns a pair 'first' is pos iterator and 'second' is bool. 
                    if second = true, first = newKV iter.
                    if second = false, first = dupkey iter.
    iterating: m.begin(), m.end() etc
    find(key) // log(n)
    erase(itr) 
    or 
    erase(key)
*/

#include <iostream>
#include <map>
#include <string>
#include <string_view>
 
void print_map(std::string_view comment, const std::map<std::string, int>& m) {
    std::cout << comment;
    // Iterate using C++17 facilities
    for (const auto& [key, value] : m)
        std::cout << '[' << key << "] = " << value << "; ";
 
// C++11 alternative:
//  for (const auto& n : m)
//      std::cout << n.first << " = " << n.second << "; ";
//
// C++98 alternative:
//  for (std::map<std::string, int>::const_iterator it = m.begin(); it != m.end(); ++it)
//      std::cout << it->first << " = " << it->second << "; ";
 
    std::cout << '\n';
}
 
void test_multimap (void) {
    std::multimap<int, std::string> myMultimap;

    // Adding elements to the multimap
    myMultimap.insert(std::make_pair(1, "Apple"));
    myMultimap.insert(std::make_pair(2, "Banana"));
    myMultimap.insert(std::make_pair(1, "Apricot")); // Duplicate key

    // Printing elements of the multimap
    std::cout << "Multimap elements:" << std::endl;
    for (const auto& pair : myMultimap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Deleting only one element with a specific key
    int keyToDelete = 1;
    auto it = myMultimap.find(keyToDelete);
    if (it != myMultimap.end()) {
        myMultimap.erase(it);
    }
    // Printing elements of the multimap after deletion
    std::cout << "\nMultimap elements after deletion of key " << keyToDelete << ":" << std::endl;
    for (const auto& pair : myMultimap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Deleting elements with a specific key
    keyToDelete = 1;
    auto range = myMultimap.equal_range(keyToDelete);
    myMultimap.erase(range.first, range.second);

    // Printing elements of the multimap after deletion
    std::cout << "\nMultimap elements after deletion of key " << keyToDelete << ":" << std::endl;
    for (const auto& pair : myMultimap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

int main() {
    // Create a map of three (string, int) pairs
    std::map<std::string, int> m{{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};
 
    print_map("1) Initial map: ", m);
 
    m["CPU"] = 25; // update an existing value
    m["SSD"] = 30; // insert a new value
    // insert another key value pair
    const auto [it, success] = m.insert(std::pair{"IO", 55});

    print_map("2) Updated map: ", m);
 
    // Using operator[] with non-existent key always performs an insert
    std::cout << "3) m[UPS] = " << m["UPS"] << '\n';
    print_map("4) Updated map: ", m);
 
    m.erase("GPU");
    print_map("5) After erase: ", m);
 
    std::erase_if(m, [](const auto& pair){ return pair.second > 25; });
    print_map("6) After erase: ", m);
    std::cout << "7) m.size() = " << m.size() << '\n';
 
    m.clear();
    std::cout << std::boolalpha << "8) Map is empty: " << m.empty() << '\n';

    test_multimap();
}