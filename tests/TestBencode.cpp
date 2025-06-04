#include "../parser/BencodeParser.h"
#include <iostream>

void printValue(const BencodeValue &value, int indent = 0)
{
    BencodeType type = value.getType();

    for (int i = 0; i < indent; ++i)
    {
        std::cout << ' ';
    }

    switch (type)
    {
    case BencodeType::Integer:
        std::cout << "int: " << value.asInt() << std::endl;
        break;

    case BencodeType::String:
        std::cout << "string: " << value.asString().c_str() << std::endl;
        break;

    case BencodeType::List:
    {
        std::cout << "list: [\n";
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
        std::cout << "dict: {\n";
        const MyUnorderedMap<MyString, BencodeValue> &dict = value.asDict();
        for (size_t i = 0; i < dict.getSize(); ++i)
        {
            const auto &entry = dict[i];
            for (int j = 0; j < indent + 2; ++j)
            {
                std::cout << ' ';
            }
            std::cout << entry.key.c_str() << ": ";
            printValue(entry.value, indent + 4);
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

int main()
{
    MyString data = "d4:spam4:eggse";

    try
    {
        BencodeParser parser(data);
        BencodeValue result = parser.parse();
        printValue(result);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Bencode Parsing failed: " << e.what() << std::endl;
    }

    return 0;
}
