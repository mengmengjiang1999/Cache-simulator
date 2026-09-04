# Cache Simulator

一个用 C++ 实现的可配置 Cache 替换策略模拟器，来自计算机系统相关课程作业。程序读取内存访问 trace，在指定 Cache 容量、块大小、相联度、替换策略和写分配策略后，统计命中数、缺失数和缺失率。

## 项目背景

本项目用于理解 Cache 的地址映射、组相联结构和替换策略。实现重点是将 Cache 数据与替换策略分离：Cache 负责地址解析、tag 比较及读写流程，各替换算法通过统一接口独立实现。

## 功能

- 支持直接映射、组相联和全相联（`way = 0`）
- 支持 LRU、树形 PLRU 和 Random 替换策略
- 支持写分配与不写分配的模拟
- 可配置 Cache 容量、块大小和相联度
- 输出命中数、缺失数和缺失率
- 附带多组 trace、批处理脚本、实验报告和设计文档

## 架构

```text
Cache
├── 地址解析：block offset / set index / tag
├── Cache 元数据：valid / dirty / tag
└── replacement_policy 抽象接口
    ├── policy_lru     按位存储访问顺序栈
    ├── policy_plru    按位存储伪 LRU 二叉树
    └── policy_random  随机选择 victim
```

主要文件：

- `cache/main.cpp`：命令行参数解析、trace 读取与结果输出
- `cache/cache.{h,cpp}`：Cache 结构及读写流程
- `cache/replacement_policy.{h,cpp}`：替换策略抽象基类
- `cache/policy_*.h`：LRU、PLRU 和 Random 策略实现
- `cache/trace/`：实验使用的内存访问 trace
- `实验报告.md` 与 `文档.docx`：实现思路和实验分析

## 构建

需要支持 C++11 的编译器（如 GCC 或 Clang）及 `make`。

```bash
git clone https://github.com/mengmengjiang1999/Cache-simulator.git
cd Cache-simulator/cache
make
```

也可使用 CMake：

```bash
cmake -S cache -B build
cmake --build build
```

## 运行

### 命令格式

```bash
./main <cache_size_kb> <block_size_b> <way> <policy> \
  <write_alloc> <write_through> <trace_file> [output_file]
```

| 参数 | 含义 | 可选值 / 示例 |
| --- | --- | --- |
| `cache_size_kb` | Cache 容量，单位 KB | `128` |
| `block_size_b` | Cache 块大小，单位 byte | `8` |
| `way` | 相联度；`0` 表示全相联 | `0`, `1`, `2`, `4`, `8` |
| `policy` | 替换策略 | `P_LRU`, `P_PLRU`, `P_RANDOM` |
| `write_alloc` | 写缺失时是否分配 Cache 块 | `1` 或 `0` |
| `write_through` | 写策略标记 | `1` 或 `0` |
| `trace_file` | 输入 trace 路径 | `trace/test.trace` |
| `output_file` | 可选的输出日志，以追加方式写入 | `result.log` |

### 示例

在 `cache/` 目录中运行：

```bash
./main 128 8 8 P_LRU 1 0 trace/test.trace result.log
cat result.log
```

示例输出：

```text
hit = 4 miss = 4
miss rate = 0.5
```

如果不指定 `output_file`，结果默认追加到当前目录的 `test4.log`。仓库中的 `cache/test.sh` 和其他 `.sh` 脚本提供了批量实验示例。

## Trace 格式

每行包含一个操作类型和一个十六进制地址：

```text
r 0x7fe8d76f8bc8
w 0x7fe8d76f8a88
```

- `r`：读访问
- `w`：写访问

## 已知限制

- `write_through` 参数目前仅用于标识和输出实验配置；写直达与写回尚未实现不同的数据路径或主存流量统计。
- 输入参数主要通过 `assert` 校验，应使用合法的 Cache 容量、块大小和相联度组合。
- 本项目为课程实验性质，不是周期精确的硬件仿真器。

## 说明

仓库保留了课程作业时的实验数据、输出日志和构建产物，便于还原当时的实验环境与结果。
