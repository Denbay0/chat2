#pragma once
#include <string>
#include <vector>
#include <optional>

struct HashEntry {
    std::string login;
    size_t hash;
    bool isDeleted;

    HashEntry(std::string l, size_t h)
        : login(std::move(l)), hash(h), isDeleted(false) {}
};

class HashTable {
private:
    std::vector<std::optional<HashEntry>> table;
    size_t tableSize;
    size_t count;

    size_t hashFunction(const std::string& key) const;

    size_t quadraticProbing(size_t index, size_t attempt) const;

    void rehash();

public:
    explicit HashTable(size_t size);

    bool insert(const std::string& login, size_t hash);
    bool remove(const std::string& login);
    std::optional<size_t> find(const std::string& login) const;

    size_t size() const;
};
