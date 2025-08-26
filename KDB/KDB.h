//
// Created by kid314 on 25-8-18.
//

#ifndef KDB_H
#define KDB_H
#include <atomic>
#include "../SkipList/SkipList.h"
#include "../logger/logger.h"
class KDB
{
public:
    explicit KDB(int);
    ~KDB();
    void put(std::string,std::string);
    [[nodiscard]] std::optional<std::string_view> get(const std::string&) const;
    void remove(const std::string&);
private:
    std::atomic<uint64_t> sequence;
    SkipList DB;
    logger DB_logger;
};



#endif //KDB_H
