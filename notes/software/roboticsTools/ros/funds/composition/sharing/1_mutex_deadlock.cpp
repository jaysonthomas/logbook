#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx1;
std::mutex mtx2;

void task1() {
  std::lock_guard<std::mutex> lock1(mtx1);
  std::this_thread::sleep_for(std::chrono::milliseconds(50)); // force overlap
  std::lock_guard<std::mutex> lock2(mtx2);
  std::cout << "task1 acquired both locks\n";
}

void task2() {
  std::lock_guard<std::mutex> lock2(mtx2); // <-- opposite order!
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  std::lock_guard<std::mutex> lock1(mtx1);
  std::cout << "task2 acquired both locks\n";
}

int main() {
  std::thread t1(task1);
  std::thread t2(task2);

  t1.join();
  t2.join();

  std::cout << "Done\n";
}