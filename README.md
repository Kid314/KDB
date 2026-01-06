# Tiny-Vector-DB (High-Performance Vector Storage)

![Language](https://img.shields.io/badge/language-C++-00599C.svg)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)
![License](https://img.shields.io/badge/license-MIT-blue.svg)

> **Note**: This project is evolving from a standard LSM-Tree Key-Value Store (KDB) into **Tiny-Vector-DB**, a lightweight, high-performance Vector Database designed for AI applications.

The repository is organized into two primary development tracks:
*   **`vector-db-engine`** (Upcoming): The new branch dedicated to Vector Search and AI integration.
*   **`master`**: The stable, high-performance LSM-Tree storage engine foundation.

---

## 🚀 Branch: vector-db-engine (Evolution)
**LSM-Tree Based Vector Storage Engine**

*Coming Soon* - This branch represents the transformation of the project into an AI-Native database. It builds upon the solid LSM-Tree foundation to support high-dimensional vector data, enabling efficient similarity search for RAG (Retrieval-Augmented Generation) and Recommendation Systems.

### Core Features

#### 1. Integrated Vector Search (KNN)
*   **Native Integration**: Embeds vector indexing algorithms directly into the storage layer, moving beyond simple Key-Value lookups.
*   **Similarity Search**: Supports **K-Nearest Neighbors (KNN)** search on high-dimensional vectors, serving as the core engine for AI knowledge retrieval.

#### 2. AI-Optimized Storage Layout
*   **Vector Serialization**: Optimized serialization formats for storing dense float vectors within SSTables.
*   **Hybrid Querying**: (Planned) Support for hybrid filtering (scalar filtering + vector similarity) by leveraging the ordered nature of the LSM-Tree.

---

## 🏗️ Branch: master (Foundation)
**Robust LSM-Tree Storage Engine (KDB)**

This branch contains the core implementation of a persistent Key-Value storage engine modeled after LevelDB/RocksDB. It provides the reliability and I/O performance required to underpin the upper-layer vector functionality.

### Core Architecture

#### 1. Standard LSM-Tree Architecture
*   **Hierarchical Storage**: Implements a complete Log-Structured Merge-Tree architecture.
*   **Components**:
    *   **MemTable**: In-memory write buffer implemented using a **Skiplist** (O(log n) insertion/lookup).
    *   **Immutable MemTable**: Read-only snapshot of memory data waiting for flush.
    *   **SSTable**: Disk-based Sorted String Tables for persistent storage.

#### 2. Data Reliability (WAL)
*   **Write Ahead Log**: Implements a robust logging mechanism to prevent data loss.
*   **mmap Optimization**: Utilizes `mmap` for high-speed log appending, ensuring data consistency and recoverability even in the event of a system crash.

#### 3. Performance Optimization
*   **Bloom Filter**: rapid membership testing to filter out non-existent keys, significantly reducing unnecessary disk I/O operations.
*   **LRU Block Cache**: detailed design of a Least Recently Used (LRU) cache for data blocks, drastically lowering read latency for hot data.

---

<!-- Chinese Version Starts Here -->

# Tiny-Vector-DB (高性能向量存储引擎)

> **注意**: 本项目目前正从通用的 KV 数据库 (KDB) 转型为 **Tiny-Vector-DB** (基于 LSM-Tree 的向量数据库)。项目将分为两个核心部分：**AI 向量数据库分支** 与 **LSM-Tree 存储基座分支**。

---

## 🔥 分支：vector-db-engine (转型目标)
**基于 LSM-Tree 的向量检索引擎**

*即将开启* - 该分支致力于打造具备 AI 原生特性的数据库雏形，在底层存储引擎之上集成向量计算能力，以支持大模型时代的 RAG 与推荐系统需求。

### 核心特性

#### 1. 向量检索集成 (Vector Search)
*   **存储层集成**: 在 LSM-Tree 存储层直接集成向量索引算法，打破传统 KV 存储的限制。
*   **KNN 搜索**: 支持对高维向量数据的 **KNN (最近邻)** 搜索，为 AI 应用提供高性能的相似度匹配能力。

#### 2. AI 原生架构
*   **向量化存储**: 针对稠密向量数据优化 SSTable 的存储格式与压缩策略。
*   **混合查询**: 利用 LSM-Tree 的有序性，未来将支持标量过滤与向量检索的混合查询。

---

## 🏗️ 分支：master (核心基座)
**高性能 LSM-Tree 分层存储引擎**

该分支是整个数据库的基石，实现了一个工业级的 KV 存储引擎，为上层向量检索提供持久化与高吞吐支持。

### 核心技术栈

#### 1. 存储引擎核心 (LSM-Tree)
*   **分层架构**: 实现了标准的 LSM-Tree 分层存储架构，写入性能极佳。
*   **组件实现**:
    *   **MemTable**: 基于 **跳表 (Skiplist)** 实现的高效内存读写结构。
    *   **Immutable MemTable**: 冻结的内存表，用于后台异步落盘。
    *   **SSTable**: 磁盘上的有序字符串表，支持高效的范围查询。

#### 2. 数据可靠性 (WAL)
*   **预写式日志**: 引入 **Write Ahead Log (WAL)** 机制，所有修改操作先写日志再写内存。
*   **Crash Safe**: 利用 `mmap` 技术进行高效的日志写入，确保系统在异常崩溃（Crash）时的数据一致性与可恢复性。

#### 3. 极致性能优化
*   **Bloom Filter**: 实现了布隆过滤器，用于快速判断 Key 是否不存在，从而避免无效的磁盘 I/O 开销。
*   **LRU Block Cache**: 设计了基于 LRU 策略的 **Block Cache**，缓存热点数据块（Block），大幅降低读延迟。
