# Torrent-Client (MVP - Torrent File Parser)

🎯 **Project Goal:**

This project is a Minimal Viable Product (MVP) that **reads, parses, and extracts data from `.torrent` files**. It does not use any external libraries and includes custom implementations of common data structures. The project can be extended in the future to become a fully-featured BitTorrent client.

---

## 🧠 How it works

`.torrent` files use a format called **Bencode**, which is a simple textual serialization method. This project includes:

- A **Bencode parser** that reads raw bytes and produces a structured tree of `BencodeValue` objects.
- A **TorrentFile** class that interprets the structure of the parsed Bencode data.
- A **TorrentFileBuilder** that builds `TorrentFile` objects step-by-step.
- A **TorrentFileFactory** that offers a simple interface for creating `TorrentFile` objects from file or bytes.

---

## 🧱 Project Structure

```
Torrent-Client/
│
├── core/
│   ├── TorrentFile.h / .cpp
│   ├── TorrentFileBuilder.h / .cpp
│   └── TorrentFileFactory.h / .cpp
│
├── parser/
│   ├── BencodeValue.h / .cpp
│   └── BencodeParser.h / .cpp
│
├── data-structures/
│   ├── MyString.h / .cpp
│   ├── MyVector.hpp
│   └── MyUnorderedMap.hpp
│
├── tests/
│   ├── TestMyVector.cpp
│   └── TestBencode.cpp
│
├── main.cpp         # Entry point
└── Makefile
```

---

## 🧰 Design Patterns

| Pattern     | Usage Location       | Purpose                                                   |
| ----------- | -------------------- | --------------------------------------------------------- |
| **Builder** | `TorrentFileBuilder` | Step-by-step construction of a `TorrentFile` from Bencode |
| **Factory** | `TorrentFileFactory` | Centralized creation of `TorrentFile` instances           |

---

## 🚀 Usage

### Compile:

```bash
make
```

### Run `.torrent` file parser:

```bash
./torrent_test path/to/file.torrent
```

### Run tests:

```bash
make run_TestMyVector
make run_TestBencode
```

---

## 🛠️ Future Improvements

- Implement Piece / Block / Peer logic
- Tracker and DHT support
- File downloading
- User GUI

---

## 📜 Example

A sample `.torrent` file (in Bencode):

```bencode
d
  4:info
    d
      4:name 5:hello
      6:length i12345e
    e
  8:announce 14:http://tracker
e
```

Will be interpreted as:

- Name: `hello`
- Size: 12345 bytes
- Tracker: `http://tracker`

---
