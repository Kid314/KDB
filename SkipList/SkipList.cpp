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

Node::Node(std::string&& new_key,std::string&& new_value, int node_level,uint64_t new_sequence,Option new_option)\
:key(std::move(new_key),new_sequence,new_option),value(std::move(new_value)),level(node_level)
{
    forward.resize(node_level,nullptr);
}

std::optional<std::string_view> SkipList::get(const std::string& request_key) const
{
    Node* help=head;
    for (int i=current_level-1;i>=0;--i)
    {
        while (help->forward[i]!=nullptr&&help->forward[i]->key.key<request_key)
        {
            help=help->forward[i];
        }
    }
    help=help->forward[0];
    if (help!=nullptr&&help->key.option!=Option::Deleted&&help->key.key==request_key)
    {
        return help->value;
    }
    std::cout<<"can't find\n";
    return std::nullopt;
}

void SkipList::put(std::string request_key, std::string request_value,uint64_t order)
{
    int temp_level=num_generate();
    std::vector<Node*> mem_vec;
    mem_vec.resize(max_level);
    Node* help=head;
    if (current_level<temp_level)
    {
        for (int i=current_level;i<temp_level;++i)
        {
            mem_vec[i]=head;
        }
        current_level=temp_level;
    }
    for (int i=current_level-1;i>=0;--i)
    {
        while (help->forward[i]!=nullptr&&help->forward[i]->key.key<request_key)
        {
            help=help->forward[i];
        }
        mem_vec[i]=help;
    }
    Node* new_node=new Node(std::move(request_key),std::move(request_value),temp_level,order,Option::Put);
    for (int i=0;i<temp_level;++i)
    {
        new_node->forward[i]=mem_vec[i]->forward[i];
        mem_vec[i]->forward[i]=new_node;
    }
}

void SkipList::remove(const std::string& request_key,uint64_t order)
{
    int temp_level=num_generate();
    std::vector<Node*> mem_vec;
    mem_vec.resize(max_level);
    Node* help=head;
    if (current_level<temp_level)
    {
        for (int i=current_level;i<temp_level;++i)
        {
            mem_vec[i]=head;
        }
        current_level=temp_level;
    }
    for (int i=current_level-1;i>=0;--i)
    {
        while (help->forward[i]!=nullptr&&help->forward[i]->key.key<request_key)
        {
            help=help->forward[i];
        }
        mem_vec[i]=help;
    }
    if (mem_vec[0]->forward[0]==nullptr||mem_vec[0]->forward[0]->key.key!=request_key)
    {
        printf("remove a invalid key!\n");
        return;
    }
    std::string new_value=mem_vec[0]->forward[0]->value;
    std::string new_key=request_key;
    Node* new_node=new Node(std::move(new_key),std::move(new_value),temp_level,order,Option::Deleted);
    for (int i=0;i<temp_level;++i)
    {
        new_node->forward[i]=mem_vec[i]->forward[i];
        mem_vec[i]->forward[i]=new_node;
    }
}

SkipList::SkipList(int new_max_level):max_level(new_max_level),current_level(1),gen(std::random_device{}()),dist(0,1)
{
    head=new Node("","",max_level,0,Option::Put);
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
