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

BencodeValue::BencodeValue(const BencodeValue &other)
{
    copyFrom(other);
}

BencodeValue::BencodeValue(BencodeValue &&other) noexcept
{
    moveFrom(std::move(other));
}

BencodeValue &BencodeValue::operator=(const BencodeValue &other)
{
    if (this != &other)
    {
        copyFrom(other);
    }

    return *this;
}

BencodeValue &BencodeValue::operator=(BencodeValue &&other) noexcept
{
    if (this != &other)
    {
        moveFrom(std::move(other));
    }

    return *this;
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

void BencodeValue::copyFrom(const BencodeValue &other)
{
    type = other.type;

    switch (type)
    {
    case BencodeType::Integer:
    {
        intValue = other.intValue;
        break;
    }
    case BencodeType::String:
    {
        stringValue = other.stringValue;
        break;
    }
    case BencodeType::List:
    {
        listValue = other.listValue;
        break;
    }
    case BencodeType::Dictionary:
    {
        dictValue = other.dictValue;
        break;
    }
    }
}

void BencodeValue::moveFrom(BencodeValue &&other)
{
    type = other.type;

    switch (type)
    {
    case BencodeType::Integer:
    {
        intValue = other.intValue;
        break;
    }
    case BencodeType::String:
    {
        stringValue = std::move(other.stringValue);
        break;
    }
    case BencodeType::List:
    {
        listValue = std::move(other.listValue);
        break;
    }
    case BencodeType::Dictionary:
    {
        dictValue = std::move(other.dictValue);
        break;
    }
    }
}