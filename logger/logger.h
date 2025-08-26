//
// Created by kid314 on 25-8-25.
//

#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <fstream>

class logger
{
public:
    logger();
    ~logger();
    void write(const std::string&,const std::string&,uint64_t);//add
    void write(const std::string&,uint64_t);//remove
private:
    std::ofstream file;
};



#endif //LOGGER_H
