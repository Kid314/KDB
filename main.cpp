#include "SkipList/SkipList.h"
#include <iostream>
int main()
{
    SkipList list1(4);
    list1.put("a","b");
    auto result=list1.get("a");

    if (result!=std::nullopt)
        std::cout<<*result<<"\n";

    list1.put("a","c");
    if (result!=std::nullopt)
        std::cout<<*result<<"\n";

    list1.remove("a");
    result=list1.get("a");
    if (result!=std::nullopt)
        std::cout<<*result<<"\n";
    return 0;
}