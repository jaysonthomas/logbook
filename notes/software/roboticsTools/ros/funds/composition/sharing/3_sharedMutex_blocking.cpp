#include <chrono>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

class DataStore {
  std::mutex mtx_;
  int data_ = 0;

public:
  int read() const {
    // note: std::mutex can't be locked from a const method without
    // making it mutable — shown here for the comparison
    std::lock_guard<std::mutex> lock(const_cast<std::mutex &>(mtx_));
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    return data_;
  }

  void write(int value) {
    std::lock_guard<std::mutex> lock(mtx_);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    data_ = value;
  }
};

int main() {
  DataStore store;
  std::vector<std::thread> threads;

  auto start = std::chrono::steady_clock::now();

  // 10 reader threads — but they run ONE AT A TIME
  for (int i = 0; i < 10; ++i) {
    threads.emplace_back([&store] {
      int v = store.read();
      (void)v;
    });
  }

  for (auto &t : threads)
    t.join();

  auto end = std::chrono::steady_clock::now();
  std::cout << "Mutex version, 10 reads took: "
            << std::chrono::duration<double>(end - start).count()
            << " seconds\n";
}