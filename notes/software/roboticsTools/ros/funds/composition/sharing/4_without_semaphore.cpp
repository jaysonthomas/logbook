#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <mutex>

// We WANT only 3 threads to use the "resource" at once,
// but nothing here actually enforces that limit.
std::atomic<int> activeConnections{0};
std::atomic<int> maxObserved{0};
std::mutex coutMutex;

void useResource(int id) {
    // Nothing blocks entry here — every thread just barges in
    int current = ++activeConnections;

    int prevMax = maxObserved.load();
    while (current > prevMax && !maxObserved.compare_exchange_weak(prevMax, current)) {}

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Thread " << id << " acquired resource. Active: " << current << "\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // simulate work

    --activeConnections;
}

int main() {
    const int NUM_THREADS = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i)
        threads.emplace_back(useResource, i);

    for (auto& t : threads)
        t.join();

    std::cout << "\nMax concurrent 'connections' used: " << maxObserved
              << " (pool was only supposed to allow 3!)\n";
}
