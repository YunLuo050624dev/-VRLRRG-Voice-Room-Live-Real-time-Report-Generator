# Voice-Room-Live-Real-time-Report-Generator

## 概述

Voice-Room-Live-Real-time-Report-Generator 是由 YunLuo 开发的实时报表生成工具，专为抖音千广工会及其他非8人麦语音厅直播工作群设计。

## 功能特性

- 厅信息管理（厅名称、主持信息）
- 实时计数器管理（喊活、新付、拉新、建联、二消、三关）
- 主持动态表格管理（添加/删除主持）
- 档位时间选择
- 一键复制数据到剪贴板
- 目标值设定

## 文档

- [编译指南](Docs/Build_CN.md) - 如何编译项目
- [开发指南](Docs/Develop_CN.md) - 如何开发和扩展项目
- [UI库接入指南](Docs/ImportTheUILibrary_CN.md) - 如何接入其他C++ UI库（本项目默认使用Win原生UI）

## 项目结构

```
Voice-Room-Live-Real-time-Report-Generator/
├── Build/              # 编译中间文件
├── Out/                # 输出可执行文件
├── Src/                # 源代码
│   ├── main.cpp
│   ├── DataStructures.h
│   ├── Resource.h
│   ├── TargetDialog.h/cpp
│   └── TimePickerDialog.h/cpp
├── Docs/               # 文档
│   ├── Build.md
│   ├── Build_CN.md
│   ├── Develop.md
│   ├── Develop_CN.md
│   ├── ImportTheUILibrary.md
│   └── ImportTheUILibrary_CN.md
├── CMakeLists.txt
├── README.md
├── README_CN.md
└── LICENSE             # Apache License 2.0
```

## 许可证

本项目采用 Apache License 2.0 许可证 - 详见 [LICENSE](LICENSE) 文件。

## 版权

Copyright 2026 YunLuo
