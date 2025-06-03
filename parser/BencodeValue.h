#pragma once

#include "../data-structures/MyString.h"
#include "../data-structures/MyVector.h"
#include "../data-structures/MyUnorderedMap.h"

enum class BencodeType
{
    Integer,
    String,
    List,
    Dictionary
};

class BencodeValue
{
public:
    BencodeValue();
    BencodeValue(int value);
    BencodeValue(const MyString &value);
    BencodeValue(const MyVector<BencodeValue> &list);
    BencodeValue(const MyUnorderedMap<MyString, BencodeValue> &dict);

    BencodeValue(const BencodeValue &other);
    BencodeValue(BencodeValue &&other) noexcept;
    BencodeValue &operator=(const BencodeValue &other);
    BencodeValue &operator=(BencodeValue &&other) noexcept;

    BencodeType getType() const;

    int asInt() const;
    const MyString &asString() const;
    const MyVector<BencodeValue> &asList() const;
    const MyUnorderedMap<MyString, BencodeValue> &asDict() const;

private:
    BencodeType type;

    int intValue;
    MyString stringValue;
    MyVector<BencodeValue> listValue;
    MyUnorderedMap<MyString, BencodeValue> dictValue;

    void copyFrom(const BencodeValue &other);
    void moveFrom(BencodeValue &&other);
};