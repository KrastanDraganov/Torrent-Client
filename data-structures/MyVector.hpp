#pragma once

#include <iostream>

template <typename T>
class MyVector
{
public:
    MyVector();
    MyVector(size_t initialCapacity);

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

template <typename T>
MyVector<T>::MyVector() : data(nullptr), size(0), capacity(0) {}

template <typename T>
MyVector<T>::MyVector(size_t initialCapacity)
    : size(0), capacity(initialCapacity)
{
    data = new T[capacity]();
    size = capacity;
}

template <typename T>
MyVector<T>::MyVector(const MyVector &other) : size(other.size), capacity(other.capacity)
{
    data = new T[capacity];

    for (size_t i = 0; i < size; ++i)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
MyVector<T>::MyVector(MyVector &&other) noexcept : data(other.data), size(other.size), capacity(other.capacity)
{
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template <typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

template <typename T>
MyVector<T> &MyVector<T>::operator=(MyVector &&other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

template <typename T>
MyVector<T>::~MyVector()
{
    free();
}

template <typename T>
void MyVector<T>::push_back(const T &value)
{
    if (size == capacity)
    {
        resize(capacity == 0 ? 1 : capacity * 2);
    }

    data[size] = value;
    ++size;
}

template <typename T>
void MyVector<T>::pop_back()
{
    if (size == 0)
    {
        throw std::out_of_range("Cannot pop from empty vector");
    }

    --size;
}

template <typename T>
size_t MyVector<T>::getSize() const
{
    return size;
}

template <typename T>
size_t MyVector<T>::getCapacity() const
{
    return capacity;
}

template <typename T>
bool MyVector<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
T &MyVector<T>::operator[](size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of bounds in MyVector");
    }

    return data[index];
}

template <typename T>
const T &MyVector<T>::operator[](size_t index) const
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of bounds in MyVector");
    }

    return data[index];
}

template <typename T>
void MyVector<T>::clear()
{
    size = 0;
}

template <typename T>
void MyVector<T>::resize(size_t newCapacity)
{
    T *newData = new T[newCapacity];

    for (size_t i = 0; i < size; ++i)
    {
        newData[i] = data[i];
    }

    delete[] data;

    data = newData;
    capacity = newCapacity;
}

template <typename T>
void MyVector<T>::copyFrom(const MyVector &other)
{
    size = other.size;
    capacity = other.capacity;

    data = new T[capacity];

    for (size_t i = 0; i < size; ++i)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
void MyVector<T>::moveFrom(MyVector &&other)
{
    data = other.data;
    size = other.size;
    capacity = other.capacity;

    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template <typename T>
void MyVector<T>::free()
{
    delete[] data;
    data = nullptr;

    size = 0;
    capacity = 0;
}
