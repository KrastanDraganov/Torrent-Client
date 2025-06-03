#pragma once

#include "MyVector.h"

template <typename Key, typename Value>
class MyUnorderedMap
{
public:
    MyUnorderedMap();
    MyUnorderedMap(const MyUnorderedMap &other);
    MyUnorderedMap(MyUnorderedMap &&other) noexcept;

    MyUnorderedMap &operator=(const MyUnorderedMap &other);
    MyUnorderedMap &operator=(MyUnorderedMap &&other) noexcept;

    ~MyUnorderedMap();

    void insert(const Key &key, const Value &value);
    bool contains(const Key &key) const;

    Value &operator[](const Key &key);
    const Value &at(const Key &key) const;

    size_t getSize() const;
    void clear();

private:
    struct Entry
    {
        Key key;
        Value value;
    };

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