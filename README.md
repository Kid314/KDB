# KDB

A LevelDB-like Key-Value Storage Engine written in C++.

This project is a hands-on exercise to build a persistent, high-performance key-value store from scratch, inspired by the architecture of LevelDB. The main goal is to practice modern C++ and gain a deep understanding of storage system internals.

## Project Name

**KDB** - Just a fun name for my database project! :)

## Current Status & Roadmap

This project is currently under active development. Here is the planned roadmap:

*   [x] **In-Memory MemTable**: Core in-memory data structure using a Skip List.
*   [ ] **Write-Ahead Log (WAL)**: For ensuring data durability against crashes.
*   [ ] **SSTable Flushing**: Flushing the in-memory MemTable to an immutable, sorted file (SSTable) on disk.
*   [ ] **Multi-Level Lookup**: Reading data from the MemTable and multiple SSTable levels on disk.
*   [ ] **Compaction**: Background process to merge SSTable files, discard deleted/overwritten data, and maintain performance.
*   [ ] **Block Cache**: Caching SSTable blocks in memory to speed up reads.
*   [ ] **Concurrency Control**: Making the database safe for multi-threaded access.

## Purpose

This project primarily serves as a C++ practice ground, focusing on:
*   Advanced Data Structures (Skip List)
*   System Design & Architecture (LSM-Tree)
*   File I/O and Memory Management
*   Concurrency and Performance Optimization

---
<br>

# KDB (中文版)

一个使用 C++ 实现的类 LevelDB 键值存储引擎。

这是一个从零开始构建一个持久化、高性能键值存储的练手项目，其架构设计受到了 LevelDB 的启发。主要目标是练习现代 C++ 并深入理解存储系统的内部工作原理。

## 项目名称

**KDB** - 哈哈哈，就是给我自己的数据库起的一个好玩的名字！:)

## 当前状态与路线图

本项目正在积极开发中。以下是计划的开发路线图：

*   [x] **内存中的 MemTable**: 基于跳表实现的核心内存数据结构。
*   [ ] **预写日志 (WAL)**: 用于保证数据在程序崩溃后不丢失的持久化机制。
*   [ ] **SSTable 刷盘**: 将内存中的 MemTable 转储为磁盘上不可变的有序字符串表文件 (SSTable)。
*   [ ] **多层级查找**: 实现从内存 MemTable 和磁盘上多层级 SSTable 中读取数据。
*   [ ] **后台合并 (Compaction)**: 通过后台进程合并 SSTable 文件，清理被删除或覆盖的数据，以维持系统性能。
*   [ ] **块缓存 (Block Cache)**: 在内存中缓存 SSTable 的数据块以加速读取性能。
*   [ ] **并发控制**: 使数据库能够安全地被多线程访问。

## 项目目的

本项目主要作为 C++ 的练手项目，专注于以下几个方面：
*   高级数据结构 (跳表)
*   系统设计与架构 (LSM-Tree)
*   文件 I/O 与内存管理
*   并发编程与性能优化