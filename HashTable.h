#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2526_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {
  private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;
    
    int h(std::string key) {
      int sum = 0;
      for (int i = 0; i < key.length(); i++) {
        sum += int(key.at(i));
      }
      return sum % max;
    }

  public:
    HashTable(int size) {
      max = size;
      n = 0;
      table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(std::string key, V value) override {
        int index = h(key);
        TableEntry<V> entry(key, value);
        
        int pos = table[index].search(entry);
        if (pos != -1) {
            throw std::runtime_error("Key already exists in dictionary");
        } else {
            table[index].prepend(entry);
            n++;
        }
    }

    V search(std::string key) override {
        int index = h(key);
        TableEntry<V> tempEntry(key);
        
        int pos = table[index].search(tempEntry);
        if (pos != -1) {
            return table[index].get(pos).value;
        } else {
            throw std::runtime_error("Key not found in dictionary");
        }
    }

    V remove(std::string key) override {
        int index = h(key);
        TableEntry<V> tempEntry(key);
        
        int pos = table[index].search(tempEntry);
        if (pos != -1) {
            V value = table[index].get(pos).value;
            table[index].remove(pos);
            n--;
            return value;
        } else {
            throw std::runtime_error("Key not found in dictionary");
        }
    }
    
    int entries() override {
        return n;
    }

    int capacity() const {
        return max;
    }

    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
        out << "HashTable (entries: " << th.n << ", capacity: " << th.max 
            << ")" << std::endl;
        
        for (int i = 0; i < th.max; i++) {
            out << "Bucket " << i << " [" << th.table[i].size() << "]: ";
            if (th.table[i].size() == 0) {
                out << "empty";
            } else {
                out << th.table[i];
            }
            out << std::endl;
        }
        return out;
    }

    V operator[](std::string key) {
        int index = h(key);
        TableEntry<V> tempEntry(key);
        
        int pos = table[index].search(tempEntry);
        if (pos != -1) {
            return table[index].get(pos).value;
        } else {
            throw std::runtime_error("Key not found in dictionary");
        }
    }
};

#endif
