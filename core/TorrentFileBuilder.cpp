#include "TorrentFileBuilder.h"

#include "../parser/BencodeParser.h"

#include <fstream>

TorrentFileBuilder &TorrentFileBuilder::fromBytes(const MyString &raw)
{
    BencodeParser parser(raw);
    BencodeValue root = parser.parse();

    return fromBencode(root);
}

TorrentFileBuilder &TorrentFileBuilder::fromBencode(const BencodeValue &root)
{
    parseRoot(root);

    return *this;
}

TorrentFileBuilder &TorrentFileBuilder::setBencodeRoot(const BencodeValue &root)
{
    return fromBencode(root);
}

TorrentFileBuilder &TorrentFileBuilder::setRawContent(const MyString &raw)
{
    return fromBytes(raw);
}

TorrentFile TorrentFileBuilder::build() const
{
    return torrent;
}

void TorrentFileBuilder::parseRoot(const BencodeValue &root)
{
    if (root.getType() != BencodeType::Dictionary)
    {
        throw std::runtime_error("Invalid torrent file: root must be a dictionary");
    }

    const MyUnorderedMap<MyString, BencodeValue> &dict = root.asDict();

    if (!dict.contains("announce") || !dict.contains("info"))
    {
        throw std::runtime_error("Missing required fields in torrent file");
    }

    torrent.setAnnounce(dict.at("announce").asString());

    parseInfo(dict.at("info"));
}

void TorrentFileBuilder::parseInfo(const BencodeValue &infoVal)
{
    if (infoVal.getType() != BencodeType::Dictionary)
    {
        throw std::runtime_error("Invalid 'info' field");
    }

    const auto &infoDict = infoVal.asDict();

    if (!infoDict.contains("piece length") || !infoDict.contains("pieces") || !infoDict.contains("name"))
    {
        throw std::runtime_error("Missing required fields in info dictionary");
    }

    torrent.setPieceLength(infoDict.at("piece length").asInt());
    torrent.setName(infoDict.at("name").asString());

    if (infoDict.contains("length"))
    {
        parseSingleFile(infoDict);
    }
    else if (infoDict.contains("files"))
    {
        parseMultiFile(infoDict);
    }
    else
    {
        throw std::runtime_error("Unknown file mode in info dictionary");
    }

    splitPieces(infoDict.at("pieces").asString());
}

void TorrentFileBuilder::parseSingleFile(const MyUnorderedMap<MyString, BencodeValue> &infoDict)
{
    long long length = infoDict.at("length").asInt();
    MyString name = infoDict.at("name").asString();

    FileEntry entry{name, length};

    MyVector<FileEntry> files;
    files.push_back(entry);

    torrent.setFiles(files);
    torrent.setTotalSize(length);
}

void TorrentFileBuilder::parseMultiFile(const MyUnorderedMap<MyString, BencodeValue> &infoDict)
{
    const auto &filesList = infoDict.at("files").asList();

    MyVector<FileEntry> entries;
    long long total = 0;

    for (size_t i = 0; i < filesList.getSize(); ++i)
    {
        const auto &fileDict = filesList[i].asDict();

        long long size = fileDict.at("length").asInt();
        const auto &pathList = fileDict.at("path").asList();

        MyString fullPath;

        for (size_t j = 0; j < pathList.getSize(); ++j)
        {
            fullPath += pathList[j].asString();

            if (j < pathList.getSize() - 1)
            {
                fullPath += "/";
            }
        }

        entries.push_back({fullPath, size});
        total += size;
    }

    torrent.setFiles(entries);
    torrent.setTotalSize(total);
}

void TorrentFileBuilder::splitPieces(const MyString &piecesRaw)
{
    MyVector<MyString> pieces;
    size_t length = piecesRaw.getSize();

    for (size_t i = 0; i + 20 <= length; i += 20)
    {
        pieces.push_back(piecesRaw.substr(i, 20));
    }

    torrent.setPieces(pieces);
}