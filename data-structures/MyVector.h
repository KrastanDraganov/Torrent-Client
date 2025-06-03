#pragma once

#include <iostream>

template <typename T>
class MyVector
{
public:
    MyVector();

    MyVector(const MyVector &other);
    MyVector(MyVector &&other) noexcept;

    MyVector &operator=(const MyVector &other);
    MyVector &operator=(MyVector &&other) noexcept;

    ~MyVector();

    void push_back(const T &value);
    void pop_back();

    size_t getSize() const;
    size_t getCapacity() const;

    bool isEmpty() const;

    T &operator[](size_t index);
    const T &operator[](size_t index) const;

    void clear();

private:
    void resize(size_t newCapacity);

    void copyFrom(const MyVector &other);
    void moveFrom(MyVector &&other);

    void free();

    T *data;

    size_t size;
    size_t capacity;
};
