#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx1;
std::mutex mtx2;

void task1() {
  std::scoped_lock lock(mtx1, mtx2); // order doesn't matter now
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  std::cout << "task1 acquired both locks\n";
}

void task2() {
  std::scoped_lock lock(mtx2, mtx1); // reversed order, still safe
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  std::cout << "task2 acquired both locks\n";
}

int main() {
  std::thread t1(task1);
  std::thread t2(task2);

  t1.join();
  t2.join();

  std::cout << "Done\n";
}