#include <iostream>
#include "KDB/KDB.h"

int main()
{
    try
    {
        KDB my_db(4);
        //my_db.put("hello","kid314");
        std::optional<std::string_view> result=my_db.get("kid314");
        if (result!=std::nullopt)
        {
            std::cout<<*result<<"\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr<<e.what()<<"\n";
        return 1;
    }
    return 0;
}