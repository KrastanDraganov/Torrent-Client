#include "TorrentFileFactory.h"
#include "TorrentFileBuilder.h"

#include <fstream>
#include <stdexcept>

TorrentFile TorrentFileFactory::createFromFile(const MyString &filePath)
{
    std::ifstream in(filePath.c_str(), std::ios::binary);

    if (!in.is_open())
    {
        throw std::runtime_error("Failed to open .torrent file");
    }

    in.seekg(0, std::ios::end);
    size_t length = in.tellg();
    in.seekg(0, std::ios::beg);

    MyVector<unsigned char> buffer(length);
    for (size_t i = 0; i < length; ++i)
    {
        char currentCharacter;
        in.get(currentCharacter);

        if (in.eof())
        {
            break;
        }

        buffer[i] = currentCharacter;
    }

    MyString content(length);
    for (size_t i = 0; i < length; ++i)
    {
        content[i] = buffer[i];
    }

    return createFromBytes(content);
}

TorrentFile TorrentFileFactory::createFromBytes(const MyString &content)
{
    TorrentFileBuilder builder;
    builder.setRawContent(content);

    return builder.build();
}

TorrentFile TorrentFileFactory::createFromBencode(const BencodeValue &root)
{
    TorrentFileBuilder builder;
    builder.setBencodeRoot(root);

    return builder.build();
}