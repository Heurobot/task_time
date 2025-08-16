#pragma once
#include<iostream>
#include <vector>
#include <ctime>// <tm>c风格的事件相关
#include <chrono>
#include <iomanip>// 格式化输入输出
#include <thread>
#include <unistd.h>//POSIX 系统调用（Unix/Linux 特有）
#include <sys/wait.h>//进程等待和控制（通常配合 fork() 使用）。
#include <sstream>// 字符串流处理
#include <atomic>// 原子操作
#include <memory>//智能指针和动态内存管理
#include <string>
#include "CommonType.h"

// 任务调度器类
// 负责管理和执行定时任务
// 提供添加任务、启动和停止调度等功能
class TaskScheduler {
public:
    ~TaskScheduler();
    // 添加一个定时任务
    void addTask(const ScheduledTask& task);
    void start();
    void stop();

private:
    std::vector<ScheduledTask> tasks;
    // 任务调度状态
    std::atomic<bool> running{false};
    // 使用智能指针管理线程资源
    std::unique_ptr<std::thread> schedulerThread;
    //判断当前时间是否满足任务执行条件
    bool shouldExecute(const ScheduledTask& task, const std::tm& now) const;
    // 执行命令函数
    void executeCommand(const std::string& command) const;
};