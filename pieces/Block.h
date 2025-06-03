#pragma once

#include "../data-structures/MyVector.h"

class Block
{
public:
    Block(int offset, const MyVector<unsigned char> &data);

    int getOffset() const;
    const MyVector<unsigned char> &getData() const;

private:
    int offset;

    MyVector<unsigned char> data;
};