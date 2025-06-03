#pragma once

#include "../data-structures/MyString.h"
#include "BencodeValue.h"

class BencodeParser
{
public:
    explicit BencodeParser(const MyString &data);

    BencodeValue parse();

private:
    MyString input;
    size_t position;

    BencodeValue parseValue();
    BencodeValue parseInteger();
    BencodeValue parseString();
    BencodeValue parseList();
    BencodeValue parseDict();

    char peek() const;
    char next();

    void expect(char ch);
};