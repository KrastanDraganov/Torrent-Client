#include "data-structures/MyString.h"
#include "parser/BencodeParser.h"
#include <iostream>

void printValue(const BencodeValue &value, int indent = 0)
{
    BencodeType type = value.getType();

    switch (type)
    {
    case BencodeType::Integer:
    {
        for (int i = 0; i < indent; ++i)
        {
            std::cout << ' ';
        }

        std::cout << "int: " << value.asInt() << std::endl;

        break;
    }
    case BencodeType::String:
    {
        for (int i = 0; i < indent; ++i)
        {
            std::cout << ' ';
        }

        std::cout << "string: " << value.asString().c_str() << std::endl;

        break;
    }
    case BencodeType::List:
    {
        for (int i = 0; i < indent; ++i)
        {
            std::cout << ' ';
        }

        std::cout << "list: [" << std::endl;
        const MyVector<BencodeValue> &list = value.asList();

        for (size_t i = 0; i < list.getSize(); ++i)
        {
            printValue(list[i], indent + 2);
        }

        for (int i = 0; i < indent; ++i)
        {
            std::cout << ' ';
        }

        std::cout << "]" << std::endl;

        break;
    }
    case BencodeType::Dictionary:
    {
        for (int i = 0; i < indent; ++i)
        {
            std::cout << ' ';
        }

        std::cout << "dict: {" << std::endl;

        const MyUnorderedMap<MyString, BencodeValue> &dict = value.asDict();

        for (size_t i = 0; i < dict.getSize(); ++i)
        {
            const auto &entry = dict[i];

            for (int j = 0; j < indent + 2; ++j)
            {
                std::cout << ' ';
            }

            std::cout << entry.key.c_str() << ": ";

            const BencodeValue &val = entry.value;

            switch (val.getType())
            {
            case BencodeType::Integer:
                std::cout << "int: " << val.asInt() << " ";
                break;
            case BencodeType::String:
                std::cout << "string: " << val.asString().c_str() << " ";
                break;
            default:
                std::cout << std::endl;
                printValue(val, indent + 4);
            }
        }

        for (int i = 0; i < indent; ++i)
        {
            std::cout << ' ';
        }

        std::cout << "}" << std::endl;
        break;
    }
    }
}

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
    for (int i = 0; i < copied.getSize(); ++i)
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

    MyString data = "d4:spam4:eggse";
    // Expected Bencode dict: {"spam": "eggs"}

    try
    {
        BencodeParser parser(data);

        BencodeValue result = parser.parse();

        printValue(result);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Parsing failed: " << e.what() << std::endl;
    }

    return 0;
}