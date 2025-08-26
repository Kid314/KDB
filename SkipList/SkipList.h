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
enum class Option
{
    Put,
    Deleted
};
typedef struct Internal_key
{
    std::string key;
    uint64_t sequence;
    Option option;
    Internal_key(std::string&& new_key,uint64_t new_sequence,Option new_option):key(std::move(new_key)),sequence(new_sequence),option(new_option) {}
}internal_key;
class Node
{
public:
    std::vector<Node*> forward;
    internal_key key;
    std::string value;
    int level;
    explicit Node(std::string&&,std::string&&,int,uint64_t,Option);
};
class SkipList
{
public:
    void put(std::string,std::string,uint64_t);
    [[nodiscard]] std::optional<std::string_view> get(const std::string&) const;
    void remove(const std::string&,uint64_t);
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
