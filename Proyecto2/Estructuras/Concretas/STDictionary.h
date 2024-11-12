#pragma once
#include "KVPair.h"
#include "SplayTree.h"
#include "../Abstractas/Dictionary.h"

/*
* Clase Concreta de los STDictionary
* Escrita por el profesor en clase
*/

template <typename K, typename V>
class STDictionary: public Dictionary<K, V>
{
private:
    SplayTree<KVPair<K, V>>* pairs;
public:
    STDictionary(const STDictionary<K, V>& other) = delete;
    void operator =(const STDictionary<K, V>& other) = delete;

    STDictionary() {
        pairs = new SplayTree<KVPair<K, V>>();
    }
    ~STDictionary() {
        delete pairs;
    }
    void insert(K key, V value) {
        KVPair<K, V> p(key, value);
        pairs->insert(p);
    }
    V remove(K key) {
        KVPair<K, V> p(key);
        p = pairs->remove(p);
        return p.value;
    }
    V getValue(K key) {
        KVPair<K, V> p(key);
        p = pairs->find(p);
        return p.value;
    }
    void setValue(K key, V value) {
        KVPair<K, V> p(key, value);
        pairs->remove(p);
        pairs->insert(p);
    }
    bool contains(K key) {
        KVPair<K, V> p(key);
        return pairs->contains(p);
    }
    List<K>* getKeys() {
        List<KVPair<K, V>>* items = pairs->getElements();
        List<K>* keys = new DLinkedList<K>();
        while (!items->atEnd()) {
            auto p = items->getElement();
            keys->append(p.key);
            items->next();
        }
        delete items; 
        return keys;
    }
    List<V>* getValues() {
        List<KVPair<K, V>>* items = pairs->getElements();
        List<V>* values = new DLinkedList<V>();
        while (!items->atEnd()) {
            auto p = items->getElement();
            values->append(p.value);
            items->next(); 
        }
        delete items;
        return values;
    }
    int getSize() {
        return pairs->getSize();
    }
    void print() {
        pairs->print();
    }
};
