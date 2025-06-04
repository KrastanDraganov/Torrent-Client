#include "TorrentFile.h"

#include <fstream>
#include <stdexcept>

TorrentFile::TorrentFile(const MyString &filePath)
{
    MyString content = readFileContent(filePath);

    BencodeParser parser(content);

    BencodeValue root = parser.parse();

    parseRoot(root);
}

MyString TorrentFile::readFileContent(const MyString &filePath) const
{
    std::ifstream in(filePath.c_str(), std::ios::binary);

    if (!in)
    {
        throw std::runtime_error("Failed to open file");
    }

    MyVector<char> buffer;

    char ch;
    while (in.get(ch))
    {
        buffer.push_back(ch);
    }

    MyString result(buffer.getSize());

    for (size_t i = 0; i < buffer.getSize(); ++i)
    {
        result += buffer[i];
    }

    result += '\0';

    return result;
}

void TorrentFile::parseRoot(const BencodeValue &root)
{
    const auto &rootDict = root.asDict();
    announce = rootDict["announce"].asString();
    const BencodeValue &info = rootDict["info"];
    parseInfo(info);
}

void TorrentFile::parseInfo(const BencodeValue &infoDictVal)
{
    const auto &infoDict = infoDictVal.asDict();

    if (infoDict.contains("files"))
    {
        parseMultiFile(infoDict);
    }
    else
    {
        parseSingleFile(infoDict);
    }

    name = infoDict["name"].asString();
    pieceLength = infoDict["piece length"].asInt();

    splitPieces(infoDict["pieces"].asString());
}

void TorrentFile::parseSingleFile(const MyUnorderedMap<MyString, BencodeValue> &infoDict)
{
    FileEntry entry;

    entry.path = infoDict["name"].asString();
    entry.size = infoDict["length"].asInt();

    totalSize = entry.size;

    files.push_back(entry);
}

void TorrentFile::parseMultiFile(const MyUnorderedMap<MyString, BencodeValue> &infoDict)
{
    const auto &filesList = infoDict["files"].asList();
    totalSize = 0;

    for (size_t i = 0; i < filesList.getSize(); ++i)
    {
        const auto &fileDict = filesList[i].asDict();

        FileEntry entry;
        entry.size = fileDict["length"].asInt();
        totalSize += entry.size;

        const auto &pathList = fileDict["path"].asList();
        MyString fullPath = pathList[0].asString();

        for (size_t j = 1; j < pathList.getSize(); ++j)
        {
            fullPath += "/";
            fullPath += pathList[j].asString();
        }

        entry.path = fullPath;
        files.push_back(entry);
    }
}

void TorrentFile::splitPieces(const MyString &piecesRaw)
{
    const char *data = piecesRaw.c_str();
    size_t len = piecesRaw.getSize();

    if (len % 20 != 0)
    {
        throw std::runtime_error("Invalid pieces string length");
    }

    for (size_t i = 0; i < len; i += 20)
    {
        MyString piece(20);
        for (int j = 0; j < 20; ++j)
        {
            piece[j] = data[i + j];
        }
        pieces.push_back(piece);
    }
}

int TorrentFile::getPieceLength() const
{
    return pieceLength;
}

long long TorrentFile::getTotalSize() const
{
    return totalSize;
}

const MyString &TorrentFile::getAnnounce() const
{
    return announce;
}

const MyString &TorrentFile::getName() const
{
    return name;
}

const MyVector<FileEntry> &TorrentFile::getFiles() const
{
    return files;
}

const MyVector<MyString> &TorrentFile::getPieces() const
{
    return pieces;
}
