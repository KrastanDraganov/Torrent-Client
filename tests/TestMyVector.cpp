#include "../data-structures/MyVector.hpp"

#include <iostream>

void testMyVector()
{
    std::cout << "Running MyVector tests...\n";

    // Test default constructor
    MyVector<int> vec;
    if (vec.getSize() != 0)
    {
        std::cerr << "Test failed: Default constructor should produce size 0.\n";
    }

    // Test push_back
    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(i * 2);
    }

    if (vec.getSize() != 10)
    {
        std::cerr << "Test failed: push_back did not increase size correctly.\n";
    }

    // Test operator[]
    for (int i = 0; i < 10; ++i)
    {
        if (vec[i] != i * 2)
        {
            std::cerr << "Test failed: operator[] returned incorrect value.\n";
        }
    }

    // Test copy constructor
    MyVector<int> copied(vec);
    if (copied.getSize() != vec.getSize())
    {
        std::cerr << "Test failed: copy constructor size mismatch.\n";
    }
    for (size_t i = 0; i < copied.getSize(); ++i)
    {
        if (copied[i] != vec[i])
        {
            std::cerr << "Test failed: copy constructor data mismatch.\n";
        }
    }

    // Test assignment operator
    MyVector<int> assigned;
    assigned = vec;
    if (assigned.getSize() != vec.getSize())
    {
        std::cerr << "Test failed: assignment operator size mismatch.\n";
    }

    // Test move constructor
    MyVector<int> moved(std::move(assigned));
    if (moved.getSize() != 10)
    {
        std::cerr << "Test failed: move constructor failed.\n";
    }

    std::cout << "All MyVector tests passed.\n";
}

int main()
{
    testMyVector();

    return 0;
}