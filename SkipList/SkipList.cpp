//
// Created by kid314 on 25-8-6.
//

#include "SkipList.h"
#include <utility>
#include <iostream>

int SkipList::num_generate()
{
    int level=1;
    while (dist(gen)==1&&level<max_level)
    {
        level++;
    }
    return level;
}
Node::Node(std::string&& new_key,std::string&& new_value, int node_level):key(std::move(new_key)),value(std::move(new_value)),level(node_level),status(Stat::Alive)
{
    forward.resize(node_level,nullptr);
}
std::optional<std::string_view> SkipList::get(const std::string& request_key) const
{
    Node* help=head;
    for (int i=current_level-1;i>=0;--i)
    {
        while (help->forward[i]!=nullptr&&help->forward[i]->key<request_key)
        {
            help=help->forward[i];
        }
    }
    help=help->forward[0];
    if (help!=nullptr&&help->status!=Stat::Deleted&&help->key==request_key)
    {
        return help->value;
    }
    std::cout<<"can't find\n";
    return std::nullopt;
}
void SkipList::put(std::string request_key, std::string request_value)
{
    int temp_level=num_generate();
    std::vector<Node*> mem_vec;
    mem_vec.resize(max_level);
    Node* help=head;
    for (int i=current_level-1;i>=0;--i)
    {
        while (help->forward[i]!=nullptr&&help->forward[i]->key<request_key)
        {
            help=help->forward[i];
        }
        mem_vec[i]=help;
    }
    if (help->forward[0]!=nullptr&&help->forward[0]->key==request_key)
    {
        help->forward[0]->value=std::move(request_value);
        help->forward[0]->status=Stat::Alive;
        return;
    }
    if (temp_level>current_level)
    {
        for (int i=current_level;i<temp_level;++i)
        {
            mem_vec[i]=head;
        }
        current_level=temp_level;
    }
    Node* new_node=new Node(std::move(request_key),std::move(request_value),temp_level);
    for (int i=0;i<temp_level;++i)
    {
        new_node->forward[i]=mem_vec[i]->forward[i];
        mem_vec[i]->forward[i]=new_node;
    }
}
void SkipList::remove(const std::string& request_key)
{
    Node* help=head;
    for (int i=current_level-1;i>=0;--i)
    {
        while (help->forward[i]!=nullptr&&help->forward[i]->key<request_key)
        {
            help=help->forward[i];
        }
    }
    help=help->forward[0];
    if (help!=nullptr&&help->status==Stat::Alive&&help->key==request_key)
    {
        help->status=Stat::Deleted;
        return;
    }
    printf("can't find key");
}
SkipList::SkipList(int new_max_level):max_level(new_max_level),current_level(1),gen(std::random_device{}()),dist(0,1)
{
    head=new Node("","",max_level);
}
SkipList::~SkipList()
{
    Node* current=head->forward[0];
    while (current!=nullptr)
    {
        Node* next=current->forward[0];
        delete current;
        current=next;
    }
    delete head;
}
