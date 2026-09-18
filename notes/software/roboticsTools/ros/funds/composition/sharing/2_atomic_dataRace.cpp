#include <iostream>
#include <thread>
#include <vector>

int counter = 0; // plain int, not thread-safe

void increment(int times) {
  for (int i = 0; i < times; ++i) {
    counter++; // read-modify-write: NOT atomic
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
  std::cout << "Actual:   " << counter << "\n"; // usually LESS than expected
}