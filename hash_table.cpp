#include "hash_table.h"
#include <cmath>
#include <stdexcept>

HashTable::HashTable(size_t size) : tableSize(size), count(0) {
    table.resize(size);
}

size_t HashTable::hashFunction(const std::string& key) const {
    const double A = 0.6180339887; // Константа метода умножения
    size_t hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % tableSize;
    }
    return static_cast<size_t>(std::floor(tableSize * (fmod(hash * A, 1.0))));
}

size_t HashTable::quadraticProbing(size_t index, size_t attempt) const {
    return (index + attempt * attempt) % tableSize;
}

void HashTable::rehash() {
    std::vector<std::optional<HashEntry>> oldTable = table;
    tableSize *= 2;
    table.clear();
    table.resize(tableSize);
    count = 0;

    for (const auto& entry : oldTable) {
        if (entry && !entry->isDeleted) {
            insert(entry->login, entry->hash);
        }
    }
}

bool HashTable::insert(const std::string& login, size_t hash) {
    if (count >= tableSize / 2) {
        rehash();
    }

    size_t index = hashFunction(login);
    for (size_t attempt = 0; attempt < tableSize; ++attempt) {
        size_t probeIndex = quadraticProbing(index, attempt);
        if (!table[probeIndex] || table[probeIndex]->isDeleted) {
            table[probeIndex] = HashEntry(login, hash);
            ++count;
            return true;
        } else if (table[probeIndex]->login == login) {
            return false; // Логин уже существует
        }
    }
    return false; // Таблица заполнена
}

bool HashTable::remove(const std::string& login) {
    size_t index = hashFunction(login);
    for (size_t attempt = 0; attempt < tableSize; ++attempt) {
        size_t probeIndex = quadraticProbing(index, attempt);
        if (!table[probeIndex]) {
            return false; // Логин не найден
        } else if (table[probeIndex]->login == login && !table[probeIndex]->isDeleted) {
            table[probeIndex]->isDeleted = true;
            --count;
            return true;
        }
    }
    return false;
}

std::optional<size_t> HashTable::find(const std::string& login) const {
    size_t index = hashFunction(login);
    for (size_t attempt = 0; attempt < tableSize; ++attempt) {
        size_t probeIndex = quadraticProbing(index, attempt);
        if (!table[probeIndex]) {
            return std::nullopt;
        } else if (table[probeIndex]->login == login && !table[probeIndex]->isDeleted) {
            return table[probeIndex]->hash;
        }
    }
    return std::nullopt;
}

size_t HashTable::size() const {
    return count;
}
