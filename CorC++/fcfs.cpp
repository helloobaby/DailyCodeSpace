// 非抢占

#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>

std::mutex kconsolelock;
std::queue<std::thread> kThreadQueue;
int main() {
  kThreadQueue.push(std::move(std::thread([]() {
    std::lock_guard<std::mutex> lck(kconsolelock);
    std::cout << "111" << std::endl;
  })));
  kThreadQueue.push(std::move(std::thread([]() {
    std::lock_guard<std::mutex> lck(kconsolelock);
    std::cout << "222" << std::endl;
  })));
  kThreadQueue.push(std::move(std::thread([]() {
    std::lock_guard<std::mutex> lck(kconsolelock);
    std::cout << "333" << std::endl;
  })));

  while (!kThreadQueue.empty()) {
    // 获得最先进来的线程
    std::thread& current_thread = kThreadQueue.front();
    // 调度线程,阻塞执行完后返回
    current_thread.join();
    kThreadQueue.pop();
  }
  return 0;
}
