#pragma once

#include "../data-structures/MyString.h"
#include "../data-structures/MyVector.hpp"

class TorrentFile
{
public:
    void setName(const MyString &name);
    const MyString &getName() const;

    void setPieceLength(int pieceLength);
    int getPieceLength() const;

    void addPieceHash(const MyString &hash);
    const MyVector<MyString> &getPieceHashes() const;

    void addFile(const MyString &path, size_t size);
    const MyVector<MyString> &getFilePaths() const;
    const MyVector<size_t> &getFileSizes() const;

private:
    MyString name;

    int pieceLength = 0;
    MyVector<MyString> pieceHashes;

    MyVector<MyString> filePaths;
    MyVector<size_t> fileSizes;
};