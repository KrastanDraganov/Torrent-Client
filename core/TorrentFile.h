#pragma once

#include "../data-structures/MyString.h"
#include "../data-structures/MyVector.hpp"
#include "../parser/BencodeValue.h"

struct FileEntry
{
    MyString path;
    long long size;
};

class TorrentFile
{
public:
    TorrentFile() = default;

    int getPieceLength() const;
    long long getTotalSize() const;

    const MyString &getAnnounce() const;
    const MyString &getName() const;

    const MyVector<FileEntry> &getFiles() const;
    const MyVector<MyString> &getPieces() const;

    void setPieceLength(int pieceLength);
    void setTotalSize(long long totalSize);

    void setAnnounce(const MyString &announce);
    void setName(const MyString &name);

    void setFiles(const MyVector<FileEntry> &files);
    void setPieces(const MyVector<MyString> &pieces);

private:
    int pieceLength = 0;
    long long totalSize = 0;

    MyString announce;
    MyString name;

    MyVector<FileEntry> files;
    MyVector<MyString> pieces;
};