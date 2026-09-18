#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> counter{0}; // atomic int, thread-safe

void increment(int times) {
  for (int i = 0; i < times; ++i) {
    counter++; // atomic fetch-add, safe across threads
  }
}

int main() {
  const int numThreads = 4;
  const int incrementsPerThread = 100000;

  std::vector<std::thread> threads;
  for (int i = 0; i < numThreads; ++i) {
    threads.emplace_back(increment, incrementsPerThread);
  }
  for (auto &t : threads) {
    t.join();
  }

  std::cout << "Expected: " << numThreads * incrementsPerThread << "\n";
  std::cout << "Actual:   " << counter << "\n"; // always matches expected
}