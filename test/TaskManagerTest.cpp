#include "TaskManager.h"
#include "Task.h"
#include "gtest/gtest.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include "TTime.h"

using namespace tmms::base;

void TestTask()
{
    TaskPtr task1 = std::make_shared<Task>(
        [](const TaskPtr &task) { std::cout << "TestTask1 " << " now:" << TTime::ISOTime()<<std::endl; }, 1000);
    TaskPtr task2 = std::make_shared<Task>(
        [](const TaskPtr &task) {
            std::cout << "TestTask2" << "now:" << TTime::ISOTime() << std::endl;
            task->Restart();
        },
        1000);
    TaskPtr task3 = std::make_shared<Task>(
        [](const TaskPtr &task) {
            std::cout << "TestTask3" << "now:" << TTime::ISOTime() << std::endl;
            task->Restart();
        },
        500);
    TaskPtr task4 = std::make_shared<Task>(
        [](const TaskPtr &task) {
            std::cout << "TestTask4" << "now:" << TTime::ISOTime() << std::endl;
            task->Restart();
        },
        30000);
    sTaskManager->Add(task1);
    sTaskManager->Add(task2);
    sTaskManager->Add(task3);
    sTaskManager->Add(task4);
}

TEST(TaskManagerTest, BasicFunctionality)
{
    TestTask();
    for (int i = 0; i < 100; ++i) // 限制循环次数以避免无限执行
    {
        sTaskManager->OnWork();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}