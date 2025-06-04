#pragma once

#include "../data-structures/MyString.h"
#include "../data-structures/MyVector.hpp"

#include "../parser/BencodeValue.h"
#include "../parser/BencodeParser.h"

struct FileEntry
{
    MyString path;
    long long size;
};

class TorrentFile
{
public:
    TorrentFile(const MyString &filePath);

    int getPieceLength() const;
    long long getTotalSize() const;

    const MyString &getAnnounce() const;
    const MyString &getName() const;

    const MyVector<FileEntry> &getFiles() const;
    const MyVector<MyString> &getPieces() const;

private:
    int pieceLength;
    long long totalSize;

    MyString announce;
    MyString name;

    MyVector<FileEntry> files;
    MyVector<MyString> pieces;

    void parseRoot(const BencodeValue &root);
    void parseInfo(const BencodeValue &infoDict);
    void parseSingleFile(const MyUnorderedMap<MyString, BencodeValue> &infoDict);
    void parseMultiFile(const MyUnorderedMap<MyString, BencodeValue> &infoDict);
    void splitPieces(const MyString &piecesRaw);

    MyString readFileContent(const MyString &filePath) const;
};