#pragma once

#include "TorrentFile.h"

#include "../parser/BencodeValue.h"
#include "../data-structures/MyVector.hpp"
#include "../data-structures/MyString.h"

class TorrentFileBuilder
{
public:
    TorrentFileBuilder() = default;

    TorrentFileBuilder &fromBencode(const BencodeValue &root);
    TorrentFileBuilder &fromBytes(const MyString &raw);

    TorrentFileBuilder &setBencodeRoot(const BencodeValue &root);
    TorrentFileBuilder &setRawContent(const MyString &raw);

    TorrentFile build() const;

private:
    TorrentFile torrent;

    void parseRoot(const BencodeValue &root);

    void parseInfo(const BencodeValue &infoDict);

    void parseSingleFile(const MyUnorderedMap<MyString, BencodeValue> &infoDict);
    void parseMultiFile(const MyUnorderedMap<MyString, BencodeValue> &infoDict);

    void splitPieces(const MyString &piecesRaw);
};