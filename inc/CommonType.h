#pragma once

#include <string>

// 定义一个结构体来表示定时任务
struct ScheduledTask {
    int year;       // -1表示每年
    int month;      // -1表示每月
    int week;       // -1表示每周(0-6, 0=周日)
    int day;        // -1表示每天
    int hour;       // -1表示每小时
    int minute;     // -1表示每分钟
    std::string command; // 要执行的命令或程序路径
    std::string description; // 任务描述
};