#include "Piece.h"

Piece::Piece(int index, int size, const MyString &expectedHash)
{
    this->index = index;
    this->size = size;
    this->expectedHash = expectedHash;
}

int Piece::getIndex() const
{
    return index;
}

int Piece::getSize() const
{
    return size;
}

const MyString &Piece::getExpectedHash() const
{
    return expectedHash;
}

void Piece::addBlock(const Block &block)
{
    blocks.push_back(block);
}

const MyVector<Block> &Piece::getBlocks() const
{
    return blocks;
}

bool Piece::isComplete() const
{
    int totalBytes = 0;

    for (size_t i = 0; i < blocks.getSize(); ++i)
    {
        totalBytes += blocks[i].getData().getSize();
    }

    return totalBytes >= size;
}