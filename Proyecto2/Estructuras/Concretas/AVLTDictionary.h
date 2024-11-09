#pragma once
#include "AVLTree.h"
#include "KVPair.h"
#include "../Abstractas/Dictionary.h"

template <typename K, typename V>
class AVLTDictionary: public Dictionary<K, V>
{
private:
    AVLTree<KVPair<K, V>>* pairs;
public:
    AVLTDictionary(const AVLTDictionary<K, V>& other) = delete;
    void operator =(const AVLTDictionary<K, V>& other) = delete;

    AVLTDictionary() {
        pairs = new AVLTree<KVPair<K, V>>();
    }
    ~AVLTDictionary() {
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
