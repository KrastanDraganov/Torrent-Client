#include "data-structures/MyString.h"
#include "parser/BencodeParser.h"
#include <iostream>

void printValue(const BencodeValue &value, int indent = 0)
{
    const char *indentation = "  ";

    switch (value.getType())
    {
    case BencodeType::Integer:
    {
        for (int i = 0; i < indent; ++i)
        {
            std::cout << indentation;
        }

        std::cout << "int: " << value.asInt() << std::endl;

        break;
    }
    case BencodeType::String:
    {
        for (int i = 0; i < indent; ++i)
        {
            std::cout << indentation;
        }

        std::cout << "string: " << value.asString().c_str() << std::endl;

        break;
    }
    case BencodeType::List:
    {
        for (int i = 0; i < indent; ++i)
        {
            std::cout << indentation;
        }

        std::cout << "list: [" << std::endl;

        for (size_t i = 0; i < value.asList().getSize(); ++i)
        {
            printValue(value.asList()[i], indent + 1);
        }

        for (int i = 0; i < indent; ++i)
        {
            std::cout << indentation;
        }

        std::cout << "]" << std::endl;

        break;
    }
    case BencodeType::Dictionary:
    {
        for (int i = 0; i < indent; ++i)
        {
            std::cout << indentation;
        }
        std::cout << "dict: {" << std::endl;

        auto &dict = value.asDict();

        for (size_t i = 0; i < dict.getSize(); ++i)
        {
            const auto &entry = dict[i];

            for (int j = 0; j < indent + 1; ++j)
            {
                std::cout << indentation;
            }

            std::cout << entry.key.c_str() << ": ";

            printValue(entry.value, indent + 1);
        }

        for (int i = 0; i < indent; ++i)
        {
            std::cout << indentation;
        }

        std::cout << "}" << std::endl;

        break;
    }
    }
}

int main()
{
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