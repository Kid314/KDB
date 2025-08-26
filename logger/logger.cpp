//
// Created by kid314 on 25-8-25.
//

#include "logger.h"
#include <filesystem>
#include <stdexcept>

logger::logger()
{
    file.exceptions(std::ios::failbit|std::ios::badbit);
    std::string path="log/wal.log";
    try
    {
        file.open(path,std::ios::binary|std::ios::app);
    }
    catch (const std::exception& e)
    {
        std::string error_message=std::filesystem::absolute(path).string();
        throw std::runtime_error("fail to open file: "+error_message);
    }
}

logger::~logger()
{
    if (file.is_open())
    {
        file.close();
    }
}

void logger::write(const std::string& new_key, uint64_t order)
{
    //[Option(1B)][Sequence(8B)][KeySize(4B)][Key]
    auto option_code=static_cast<uint8_t>(0);
    file.write(reinterpret_cast<const char*>(&option_code),sizeof(option_code));
    file.write(reinterpret_cast<const char*>(&order),sizeof(order));
    uint32_t key_size=new_key.size();
    file.write(reinterpret_cast<const char*>(&key_size),sizeof(key_size));
    file.write(new_key.c_str(),static_cast<std::streamsize>(new_key.size()));
    file.flush();
}

void logger::write(const std::string& new_key, const std::string& new_value, uint64_t order)
{
    //[Option(1B)][Sequence(8B)][KeySize(4B)][Key][ValueSize(4B)][Value]
    auto option_code=static_cast<uint8_t>(1);
    file.write(reinterpret_cast<const char*>(&option_code),sizeof(option_code));
    file.write(reinterpret_cast<const char*>(&order),sizeof(order));
    uint32_t key_size=new_key.size();
    file.write(reinterpret_cast<const char*>(&key_size),sizeof(key_size));
    file.write(new_key.c_str(),static_cast<std::streamsize>(new_key.size()));
    uint32_t value_size=new_value.size();
    file.write(reinterpret_cast<const char*>(&value_size),sizeof(value_size));
    file.write(new_value.c_str(),static_cast<std::streamsize>(new_value.size()));
    file.flush();
}

