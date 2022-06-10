#ifndef PHOENIXSYS_STORAGE_H
#define PHOENIXSYS_STORAGE_H

#include "../structs/entry_struct.h"
#include <string>
#include <vector>
#include <fstream>

class Storage {
private:
    std::string name;
    FILE *file;
    std::vector<entry_t> entries;
    std::vector<entry_t> pending;
public:
    explicit Storage(const std::string& name);
    ~Storage();
    void add(entry_t &entry);
    int findById(uint32_t id);
    entry_t getByIndex(uint32_t index);
    void removeById(uint32_t id);
    void commit();
    void save();
    std::vector<entry_t> all();
};


#endif //PHOENIXSYS_STORAGE_H
