#pragma once

#include "Block.h"
#include "../data-structures/MyVector.hpp"
#include "../data-structures/MyString.h"

class Piece
{
public:
    Piece(int index, int size, const MyString &expectedHash);

    int getIndex() const;
    int getSize() const;
    const MyString &getExpectedHash() const;

    void addBlock(const Block &block);
    const MyVector<Block> &getBlocks() const;

    bool isComplete() const;

private:
    int index;
    int size;

    MyString expectedHash;
    MyVector<Block> blocks;
};