#pragma once

#include "MyVector.hpp"

#include <iostream>
#include <stdexcept>

template <typename Key, typename Value>
class MyUnorderedMap
{
public:
    struct Entry
    {
        Key key;
        Value value;
    };

    MyUnorderedMap();
    MyUnorderedMap(const MyUnorderedMap &other);
    MyUnorderedMap(MyUnorderedMap &&other) noexcept;

    MyUnorderedMap &operator=(const MyUnorderedMap &other);
    MyUnorderedMap &operator=(MyUnorderedMap &&other) noexcept;

    ~MyUnorderedMap();

    void insert(const Key &key, const Value &value);
    bool contains(const Key &key) const;

    Value &operator[](const Key &key);
    const Value &operator[](const Key &key) const;
    const Value &at(const Key &key) const;

    const Entry &operator[](size_t index) const;

    size_t getSize() const;
    void clear();

private:
    MyVector<MyVector<Entry>> buckets;
    size_t size;
    size_t capacity;

    size_t hash(const Key &key) const;
    void rehash();

    void copyFrom(const MyUnorderedMap &other);
    void moveFrom(MyUnorderedMap &&other);

    static constexpr double loadFactorThreshold = 0.75;
    static constexpr size_t initialCapacity = 16;
};

template <typename Key, typename Value>
MyUnorderedMap<Key, Value>::MyUnorderedMap()
{
    capacity = initialCapacity;
    buckets = MyVector<MyVector<Entry>>(capacity);
    size = 0;
}

template <typename Key, typename Value>
void MyUnorderedMap<Key, Value>::copyFrom(const MyUnorderedMap &other)
{
    buckets = other.buckets;
    size = other.size;
    capacity = other.capacity;
}

template <typename Key, typename Value>
void MyUnorderedMap<Key, Value>::moveFrom(MyUnorderedMap &&other)
{
    buckets = std::move(other.buckets);
    size = other.size;
    capacity = other.capacity;

    other.size = 0;
    other.capacity = 0;
}

template <typename Key, typename Value>
MyUnorderedMap<Key, Value>::MyUnorderedMap(const MyUnorderedMap &other)
{
    copyFrom(other);
}

template <typename Key, typename Value>
MyUnorderedMap<Key, Value>::MyUnorderedMap(MyUnorderedMap &&other) noexcept
{
    moveFrom(std::move(other));
}

template <typename Key, typename Value>
MyUnorderedMap<Key, Value> &MyUnorderedMap<Key, Value>::operator=(const MyUnorderedMap &other)
{
    if (this != &other)
    {
        clear();
        copyFrom(other);
    }

    return *this;
}

template <typename Key, typename Value>
MyUnorderedMap<Key, Value> &MyUnorderedMap<Key, Value>::operator=(MyUnorderedMap &&other) noexcept
{
    if (this != &other)
    {
        clear();
        moveFrom(std::move(other));
    }

    return *this;
}

template <typename Key, typename Value>
MyUnorderedMap<Key, Value>::~MyUnorderedMap()
{
    clear();
}

template <typename Key, typename Value>
void MyUnorderedMap<Key, Value>::insert(const Key &key, const Value &value)
{
    if ((double)size / capacity >= loadFactorThreshold)
    {
        rehash();
    }

    size_t target = hash(key) % capacity;

    for (size_t i = 0; i < buckets[target].getSize(); ++i)
    {
        if (buckets[target][i].key == key)
        {
            buckets[target][i].value = value;
            return;
        }
    }

    buckets[target].push_back({key, value});
    ++size;
}

template <typename Key, typename Value>
bool MyUnorderedMap<Key, Value>::contains(const Key &key) const
{
    size_t target = hash(key) % capacity;

    for (size_t i = 0; i < buckets[target].getSize(); ++i)
    {
        if (buckets[target][i].key == key)
        {
            return true;
        }
    }

    return false;
}

template <typename Key, typename Value>
Value &MyUnorderedMap<Key, Value>::operator[](const Key &key)
{
    size_t target = hash(key) % capacity;

    for (size_t i = 0; i < buckets[target].getSize(); ++i)
    {
        if (buckets[target][i].key == key)
        {
            return buckets[target][i].value;
        }
    }

    insert(key, Value());
    target = hash(key) % capacity;

    return buckets[target][buckets[target].getSize() - 1].value;
}

template <typename Key, typename Value>
const Value &MyUnorderedMap<Key, Value>::operator[](const Key &key) const
{
    size_t target = hash(key) % capacity;

    for (size_t i = 0; i < buckets[target].getSize(); ++i)
    {
        if (buckets[target][i].key == key)
        {
            return buckets[target][i].value;
        }
    }

    throw std::out_of_range("Key not found in const operator[]");
}

template <typename Key, typename Value>
const Value &MyUnorderedMap<Key, Value>::at(const Key &key) const
{
    size_t target = hash(key) % capacity;

    for (size_t i = 0; i < buckets[target].getSize(); ++i)
    {
        if (buckets[target][i].key == key)
        {
            return buckets[target][i].value;
        }
    }

    throw std::out_of_range("Key not found");
}

template <typename Key, typename Value>
const typename MyUnorderedMap<Key, Value>::Entry &MyUnorderedMap<Key, Value>::operator[](size_t index) const
{
    size_t count = 0;

    for (size_t i = 0; i < buckets.getSize(); ++i)
    {
        for (size_t j = 0; j < buckets[i].getSize(); ++j)
        {
            if (count == index)
            {
                return buckets[i][j];
            }

            ++count;
        }
    }

    throw std::out_of_range("Index out of bounds in MyUnorderedMap");
}

template <typename Key, typename Value>
size_t MyUnorderedMap<Key, Value>::getSize() const
{
    return size;
}

template <typename Key, typename Value>
void MyUnorderedMap<Key, Value>::clear()
{
    buckets = MyVector<MyVector<Entry>>(capacity);
    size = 0;
}

template <typename Key, typename Value>
size_t MyUnorderedMap<Key, Value>::hash(const Key &key) const
{
    size_t hashVal = 0;
    const char *str = key.c_str();

    for (size_t i = 0; i < key.getSize(); ++i)
    {
        hashVal = 31 * hashVal + str[i];
    }

    return hashVal;
}

template <typename Key, typename Value>
void MyUnorderedMap<Key, Value>::rehash()
{
    size_t oldCapacity = capacity;
    capacity *= 2;

    MyVector<MyVector<Entry>> newBuckets(capacity);

    for (size_t i = 0; i < oldCapacity; ++i)
    {
        for (size_t j = 0; j < buckets[i].getSize(); ++j)
        {
            Entry &entry = buckets[i][j];

            size_t target = hash(entry.key) % capacity;
            newBuckets[target].push_back(entry);
        }
    }

    buckets = std::move(newBuckets);
}