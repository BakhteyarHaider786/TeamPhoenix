#include "storage.h"

#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>

using std::string;
using std::sort;
using std::fopen;

Storage::Storage(const std::string& name): name(name) {
    file = fopen(("data/" + name).c_str(), "rb+");
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }

    entry_t entry;
    int size = sizeof(entry_t);

    do {
        memset(&entry, 0, size);
        fread(&entry, 1, size, file);
        if(feof(file)) {
            break;
        }
        entries.push_back(entry);
    } while (true);
    sort(entries.begin(), entries.end(), [](entry_t a, entry_t b) { return a.id < b.id; });
    fclose(file);
}

Storage::~Storage() {
    file = fopen(("data/" + name).c_str(), "rb+");
    if (!entries.empty()) {
        fseek(file, 0, SEEK_SET);
        for (auto& entry : entries) {
            fwrite(&entry, 1, sizeof(entry_t), file);
        }
    }
    fflush(file);
    fclose(file);
}

void Storage::add(entry_t &entry) {
    if (!entries.empty()) {
        entry.id = entries[entries.size() - 1].id + 1;
    } else {
        entry.id = 1;
    }
    pending.push_back(entry);
}

void Storage::commit() {
    for (auto& entry : pending) {
        entries.push_back(entry);
        pending.pop_back();
    }
    sort(entries.begin(), entries.end(), [](entry_t a, entry_t b) { return a.id < b.id; });
}

int Storage::findById(uint32_t id) {
    int index = 0;
    for (auto& entry : entries) {
        if (entry.id == id) {
            break;
        }
        index++;
    }
    if (index == entries.size() || entries[index].id != id) {
        return -1;
    }
    return index;
}

void Storage::removeById(uint32_t id) {
    int index = findById(id);
    if (index == -1) {
        return;
    }
    entries.erase(entries.begin() + index);
}

entry_t Storage::getByIndex(uint32_t index) {
    if (index > entries.size() - 1) {
        return {};
    }
    return entries[index];
}

std::vector<entry_t> Storage::all() {
    return entries;
}

void Storage::save() {
    file = fopen(("data/" + name).c_str(), "rb+");
    if (!entries.empty()) {
        fseek(file, 0, SEEK_SET);
        for (auto& entry : entries) {
            fwrite(&entry, 1, sizeof(entry_t), file);
        }
    }
    fflush(file);
    fclose(file);
}

