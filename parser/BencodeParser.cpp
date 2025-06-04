#include "BencodeParser.h"

#include <stdexcept>

BencodeParser::BencodeParser(const MyString &data)
{
    input = data;
    position = 0;
}

BencodeValue BencodeParser::parse()
{
    return parseValue();
}

BencodeValue BencodeParser::parseValue()
{
    char current = peek();

    if (current == 'i')
    {
        return parseInteger();
    }

    if (current >= '0' && current <= '9')
    {
        return parseString();
    }

    if (current == 'l')
    {
        return parseList();
    }

    if (current == 'd')
    {
        return parseDict();
    }

    throw std::logic_error("Invalid bencode value");
}

BencodeValue BencodeParser::parseInteger()
{
    expect('i');

    int value = 0;
    bool isNegative = false;

    if (peek() == '-')
    {
        isNegative = true;
        ++position;
    }

    while (peek() >= '0' && peek() <= '9')
    {
        value = value * 10 + (next() - '0');
    }

    expect('e');

    return isNegative ? BencodeValue(-value) : BencodeValue(value);
}

BencodeValue BencodeParser::parseString()
{
    int length = 0;

    while (peek() >= '0' && peek() <= '9')
    {
        length = length * 10 + (next() - '0');
    }

    expect(':');

    MyString result;

    for (int i = 0; i < length; ++i)
    {
        result += input[position];
        ++position;
    }

    return BencodeValue(result);
}

BencodeValue BencodeParser::parseList()
{
    expect('l');

    MyVector<BencodeValue> list;

    while (peek() != 'e')
    {
        list.push_back(parseValue());
    }

    expect('e');

    return BencodeValue(list);
}

BencodeValue BencodeParser::parseDict()
{
    expect('d');

    MyUnorderedMap<MyString, BencodeValue> dict;

    while (peek() != 'e')
    {
        BencodeValue key = parseString();
        BencodeValue value = parseValue();

        dict.insert(key.asString(), value);
    }

    expect('e');

    return BencodeValue(dict);
}

char BencodeParser::peek() const
{
    if (position >= input.getSize())
    {
        throw std::out_of_range("Parsing failed: position out of bounds");
    }

    return input[position];
}

char BencodeParser::next()
{
    if (position >= input.getSize())
    {
        throw std::out_of_range("Parsing failed: position out of bounds");
    }

    return input[position++];
}

void BencodeParser::expect(char ch)
{
    if (peek() != ch)
    {
        throw std::logic_error("Unexpected character during parsing");
    }

    ++position;
}