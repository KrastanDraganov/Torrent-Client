#include "core/TorrentFile.h"

#include <iostream>

void printTorrentInfo(const TorrentFile &torrent)
{
    std::cout << "Announce: " << torrent.getAnnounce().c_str() << '\n';
    std::cout << "Name: " << torrent.getName().c_str() << '\n';
    std::cout << "Total Size: " << torrent.getTotalSize() << " bytes\n";
    std::cout << "Piece Length: " << torrent.getPieceLength() << " bytes\n";

    const MyVector<MyString> &pieces = torrent.getPieces();
    std::cout << "Number of Pieces: " << pieces.getSize() << '\n';

    const MyVector<FileEntry> &files = torrent.getFiles();

    std::cout << "Files:\n";

    for (size_t i = 0; i < files.getSize(); ++i)
    {
        const FileEntry &entry = files[i];
        std::cout << "  - " << entry.path.c_str() << " (" << entry.size << " bytes)\n";
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <path to .torrent file>" << std::endl;

        return 1;
    }

    try
    {
        TorrentFile torrent(argv[1]);
        printTorrentInfo(torrent);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Torrent Parsing failed: " << e.what() << '\n';
    }

    return 0;
}