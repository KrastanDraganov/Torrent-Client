# Torrent-Client

MVP for a **Torrent File Parser**, written in C++ without any external libraries. This project lays the foundation for a full-featured torrent client by focusing first on interpreting `.torrent` metadata files using a custom-built data structure and parsing system.

## 🚀 Project Goal

The primary objective is to build a **custom Bencode parser** and use it to extract key information from `.torrent` files. These include:

- Announce URL
- File names and sizes
- Total file size
- Piece size and hashes

This parser is the **core foundation** of any BitTorrent client.

---

## 🧠 How It Works

1. **Reading `.torrent` files** into a custom `MyString` class (no `std::string`).
2. **Parsing Bencode** format using recursive descent (numbers, strings, lists, dictionaries).
3. **Constructing `TorrentFile`** objects from parsed metadata.

The implementation does not rely on STL containers. Instead, we use:

- `MyVector<T>` — a dynamic array
- `MyUnorderedMap<K, V>` — a custom hash map
- `MyString` — a string class wrapping raw char buffers

---

## 🗂️ File Structure

```
Torrent-Client/
├── core/
│ └── TorrentFile.{h,cpp} # Logic for interpreting parsed torrent metadata
├── parser/
│ ├── BencodeParser.{h,cpp} # Recursive Bencode parser
│ ├── BencodeValue.{h,cpp} # Value container for parsed Bencode data
├── data-structures/
│ ├── MyVector.hpp # Custom dynamic array implementation
│ ├── MyUnorderedMap.hpp # Custom hash map implementation
│ └── MyString.{h,cpp} # Custom string class
├── tests/
│ ├── TestBencode.cpp # Tests for Bencode parsing
│ └── TestMyVector.cpp # Tests for MyVector
├── main.cpp # Entry point (CLI + parsing test)
├── Makefile # Build system
└── README.md
```

---

## 🧰 Design Patterns Used

- **Builder Pattern**: The `TorrentFile` class splits the construction logic into multiple `parseX` methods (e.g. `parseRoot`, `parseInfo`, `parseSingleFile`, etc.), which resembles the _Builder_ design pattern.
- **RAII**

---

## Running the project

- Main torrent parser - `main && ./torrent_test "path-to-torrent-file"`
- Test for MyVector - `make run_TestMyVector`
- Test for BencodeParser - `make run_TestBencode`
