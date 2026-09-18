#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <mutex>
#include <semaphore>

// Only 3 "slots" available at a time — enforced by the semaphore itself.
std::counting_semaphore<3> resourcePool(3);

std::atomic<int> activeConnections{0};
std::atomic<int> maxObserved{0};
std::mutex coutMutex;

void useResource(int id) {
    resourcePool.acquire();   // blocks here if 3 slots are already taken

    int current = ++activeConnections;
    int prevMax = maxObserved.load();
    while (current > prevMax && !maxObserved.compare_exchange_weak(prevMax, current)) {}

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Thread " << id << " acquired resource. Active: " << current << "\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // simulate work

    --activeConnections;
    resourcePool.release();   // frees the slot for the next waiting thread
}

int main() {
    const int NUM_THREADS = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i)
        threads.emplace_back(useResource, i);

    for (auto& t : threads)
        t.join();

    std::cout << "\nMax concurrent 'connections' used: " << maxObserved
              << " (correctly capped at 3)\n";
}
