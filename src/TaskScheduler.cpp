#include "../inc/TaskScheduler.h"



TaskScheduler::~TaskScheduler() {
    stop();
}

void TaskScheduler::start() {
    if (running) return;
    
    running = true;
    schedulerThread = std::make_unique<std::thread>([this]() {
        while (running) {
            auto now = std::chrono::system_clock::now();
            std::time_t now_time = std::chrono::system_clock::to_time_t(now);
            std::tm now_tm = *std::localtime(&now_time);

            for (const auto& task : tasks) {
                if (shouldExecute(task, now_tm)) {
                    std::cout << "Executing task: " << task.description 
                              << " at " << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << std::endl;
                    executeCommand(task.command);
                }
            }

            std::this_thread::sleep_for(std::chrono::seconds(60));
        }
    });
}

void TaskScheduler::addTask(const ScheduledTask& task) {
    tasks.push_back(task);
}

void TaskScheduler::stop() {
    if (!running) return;

    running = false;
    if (schedulerThread && schedulerThread->joinable()) {
        schedulerThread->join();
    }
    schedulerThread.reset();
}

bool TaskScheduler::shouldExecute(const ScheduledTask& task, const std::tm& now) const {
    // 检查当前时间是否满足任务的执行条件
     if (task.year != -1 && (now.tm_year + 1900) != task.year) return false;
    if (task.month != -1 && (now.tm_mon + 1) != task.month) return false;
    if (task.day != -1 && now.tm_mday != task.day) return false;
    if (task.hour != -1 && now.tm_hour != task.hour) return false;
    if (task.minute != -1 && now.tm_min != task.minute) return false;
    
    if (task.week != -1) {
        int current_weekday = now.tm_wday;
        if (current_weekday != task.week) return false;
    }

    return true;
}


void TaskScheduler::executeCommand(const std::string& command) const {
    // 使用系统调用执行命令
    pid_t pid = fork();
    
    if (pid == -1) {
        std::cerr << "Failed to fork process for command: " << command << std::endl;
        return;
    } else if (pid == 0) {
        // 子进程
        std::vector<std::string> args;
        std::istringstream iss(command);
        for(std::string s; iss >> s; ) {
            args.push_back(s);
        }
        
        std::vector<char*> argv;
        for(auto& s : args) {
            argv.push_back(&s[0]);
        }
        argv.push_back(nullptr);
        
        execvp(argv[0], argv.data());
        
        std::cerr << "Failed to execute command: " << command << std::endl;
        _exit(EXIT_FAILURE);
    } else {
        // 父进程
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            std::cout << "Command exited with status: " << WEXITSTATUS(status) << std::endl;
        } else if (WIFSIGNALED(status)) {
            std::cout << "Command killed by signal: " << WTERMSIG(status) << std::endl;
        }
    }
}
