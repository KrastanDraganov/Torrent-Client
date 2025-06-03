#include "TorrentFile.h"

void TorrentFile::setName(const MyString &name)
{
    this->name = name;
}

const MyString &TorrentFile::getName() const
{
    return name;
}

void TorrentFile::setPieceLength(int pieceLength)
{
    this->pieceLength = pieceLength;
}

int TorrentFile::getPieceLength() const
{
    return pieceLength;
}

void TorrentFile::addPieceHash(const MyString &hash)
{
    pieceHashes.push_back(hash);
}

const MyVector<MyString> &TorrentFile::getPieceHashes() const
{
    return pieceHashes;
}

void TorrentFile::addFile(const MyString &path, size_t size)
{
    filePaths.push_back(path);
    fileSizes.push_back(size);
}

const MyVector<MyString> &TorrentFile::getFilePaths() const
{
    return filePaths;
}

const MyVector<size_t> &TorrentFile::getFileSizes() const
{
    return fileSizes;
}
