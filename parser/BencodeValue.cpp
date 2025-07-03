#include "BencodeValue.h"
#include <stdexcept>

BencodeValue::BencodeValue()
{
    type = BencodeType::Integer;
    intValue = 0;
}

BencodeValue::BencodeValue(int value)
{
    type = BencodeType::Integer;
    intValue = value;
}

BencodeValue::BencodeValue(const MyString &value)
{
    type = BencodeType::String;
    stringValue = value;
}

BencodeValue::BencodeValue(const MyVector<BencodeValue> &list)
{
    type = BencodeType::List;
    listValue = list;
}

BencodeValue::BencodeValue(const MyUnorderedMap<MyString, BencodeValue> &dict)
{
    type = BencodeType::Dictionary;
    dictValue = dict;
}

BencodeType BencodeValue::getType() const
{
    return type;
}

int BencodeValue::asInt() const
{
    if (type != BencodeType::Integer)
    {
        throw std::logic_error("BencodeValue is not an Integer");
    }

    return intValue;
}

const MyString &BencodeValue::asString() const
{
    if (type != BencodeType::String)
    {
        throw std::logic_error("BencodeValue is not a String");
    }

    return stringValue;
}

const MyVector<BencodeValue> &BencodeValue::asList() const
{
    if (type != BencodeType::List)
    {
        throw std::logic_error("BencodeValue is not a List");
    }

    return listValue;
}

const MyUnorderedMap<MyString, BencodeValue> &BencodeValue::asDict() const
{
    if (type != BencodeType::Dictionary)
    {
        throw std::logic_error("BencodeValue is not a Dictionary");
    }

    return dictValue;
}