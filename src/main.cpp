#include <iostream>
#include"../inc/TaskScheduler.h"
//#include"../inc/CommonType.h"

int main() {
    TaskScheduler scheduler;

    // 添加示例任务
    scheduler.addTask({
        -1,     // 每年
        -1,     // 每月
        -1,     // 每周
        15,     // 每月15日
        16,     // 16点
        3,      // 53分
        "echo hello 已经到达预定时间",
        "定时打印命令"
    });

    // scheduler.addTask({
    //     -1,     // 每年
    //     -1,     // 每月
    //     1,      // 每周一
    //     -1,     // 每天
    //     8,      // 8点
    //     30,     // 30分
    //     "/usr/local/bin/generate_report.sh",
    //     "每周一早上8:30生成报告"
    // });

    // scheduler.addTask({
    //     -1,     // 每年
    //     -1,     // 每月
    //     -1,     // 每周
    //     -1,     // 每天
    //     -1,     // 每小时
    //     0,      // 0分
    //     "/usr/bin/curl -X POST http://localhost:8080/api/healthcheck",
    //     "每小时执行一次健康检查"
    // });

    std::cout << "Starting task scheduler..." << std::endl;
    scheduler.start();

    std::cout << "Press Enter to stop the scheduler..." << std::endl;
    std::cin.get();

    scheduler.stop();
    std::cout << "Task scheduler stopped." << std::endl;

    return 0;
}