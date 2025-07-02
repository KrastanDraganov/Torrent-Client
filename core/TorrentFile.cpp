#include "TorrentFile.h"

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

void TorrentFile::setAnnounce(const MyString &announce)
{
    this->announce = announce;
}

void TorrentFile::setName(const MyString &name)
{
    this->name = name;
}

void TorrentFile::setPieceLength(int pieceLength)
{
    this->pieceLength = pieceLength;
}

void TorrentFile::setTotalSize(long long totalSize)
{
    this->totalSize = totalSize;
}

void TorrentFile::setFiles(const MyVector<FileEntry> &files)
{
    this->files = files;
}

void TorrentFile::setPieces(const MyVector<MyString> &pieces)
{
    this->pieces = pieces;
}