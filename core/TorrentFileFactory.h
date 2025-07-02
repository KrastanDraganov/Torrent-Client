#pragma once

#include "TorrentFile.h"

#include "../data-structures/MyString.h"

class TorrentFileFactory
{
public:
    static TorrentFile createFromFile(const MyString &filePath);

    static TorrentFile createFromBytes(const MyString &content);

    static TorrentFile createFromBencode(const BencodeValue &root);
};