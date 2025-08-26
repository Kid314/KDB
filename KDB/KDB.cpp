//
// Created by kid314 on 25-8-18.
//

#include "KDB.h"
#include <filesystem>
#include <stdexcept>

KDB::KDB(int level):sequence(1),DB(level)
{
    const std::string path="log/wal.log";
    std::ifstream file;
    file.exceptions(std::ios::failbit|std::ios::badbit);
    try
    {
        file.open(path,std::ios::binary|std::ios::ate);
    }
    catch (const std::exception& e)
    {
        std::string error_message=std::filesystem::absolute(path).string();
        throw std::runtime_error("can't refix or reload file: "+error_message);
    }
    if (!file.is_open())
    {
        throw std::runtime_error("can't open log:"+std::filesystem::absolute(path).string());
    }
    if (file.tellg()==0)
    {
        return;
    }
    file.seekg(0);
    uint8_t op_code;
    uint64_t max_sequence=0;
    uint64_t new_sequence;
    uint32_t key_size;
    uint32_t value_size;
    std::string new_key;
    std::string new_value;
    try
    {
        while (file.read(reinterpret_cast<char *>(&op_code), sizeof(op_code)))
        {
            file.read(reinterpret_cast<char *>(&new_sequence), sizeof(new_sequence));
            file.read(reinterpret_cast<char *>(&key_size), sizeof(key_size));
            new_key.resize(key_size);
            file.read(&new_key[0], key_size);
            if (op_code == 1)
            {
                file.read(reinterpret_cast<char *>(&value_size), sizeof(value_size));
                new_value.resize(value_size);
                file.read(&new_value[0], value_size);
                DB.put(new_key, new_value, new_sequence);
            } else if (op_code == 0)
            {
                DB.remove(new_key, new_sequence);
            }
            if (new_sequence>max_sequence)
            {
                max_sequence=new_sequence;
            }
        }
    }
    catch (const std::ios_base::failure& e)
    {
        if (!file.eof())
        {
            throw std::runtime_error("wal file is error:"+std::string(e.what()));
        }
    }
    sequence = max_sequence + 1;
    file.close();
}

KDB::~KDB()=default;

void KDB::put(std::string new_key,std::string new_value)
{
    DB_logger.write(new_key,new_value,sequence);
    DB.put(std::move(new_key),std::move(new_value),sequence);
    ++sequence;
}

std::optional<std::string_view> KDB::get(const std::string& request_key) const
{
    return DB.get(request_key);
}

void KDB::remove(const std::string& request_key)
{
    DB_logger.write(request_key,sequence);
    DB.remove(request_key,sequence);
    ++sequence;
}




