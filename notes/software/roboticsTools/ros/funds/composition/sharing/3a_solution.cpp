#include <chrono>
#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>

class DataStore {
  mutable std::shared_mutex mtx_;
  int data_ = 0;

public:
  int read() const {
    std::shared_lock<std::shared_mutex> lock(mtx_); // shared/read lock
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return data_;
  }

  void write(int value) {
    std::unique_lock<std::shared_mutex> lock(mtx_); // exclusive/write lock
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    data_ = value;
  }
};

int main() {
  DataStore store;
  std::vector<std::thread> threads;

  auto start = std::chrono::steady_clock::now();

  // 10 reader threads — these CAN run concurrently
  for (int i = 0; i < 10; ++i) {
    threads.emplace_back([&store] {
      int v = store.read();
      (void)v;
    });
  }

  for (auto &t : threads)
    t.join();

  auto end = std::chrono::steady_clock::now();
  std::cout << "shared_mutex version, 10 reads took: "
            << std::chrono::duration<double>(end - start).count()
            << " seconds\n";
}