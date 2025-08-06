//
// Created by kid314 on 25-8-6.
//

#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <string_view>
#include <optional>
#include <random>
#include <string>
#include <vector>
enum class Stat
{
    Alive,
    Deleted
};
class Node
{
public:
    std::vector<Node*> forward;
    std::string key;
    std::string value;
    Stat status;
    int level;
    explicit Node(std::string&&,std::string&&,int);
};
class SkipList
{
public:
    void put(std::string&,std::string&);
    [[nodiscard]] std::optional<std::string_view> get(const std::string&) const;
    void remove(const std::string&);
    explicit SkipList(int);
    ~SkipList();
private:
    [[nodiscard]] int num_generate();
    int current_level;
    int max_level;
    Node* head;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
};

#endif //SKIPLIST_H
