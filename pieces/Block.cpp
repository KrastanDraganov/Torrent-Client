#include "Block.h"

Block::Block(int offset, const MyVector<unsigned char> &data)
{
    this->offset = offset;
    this->data = data;
}

int Block::getOffset() const
{
    return offset;
}

const MyVector<unsigned char> &Block::getData() const
{
    return data;
}