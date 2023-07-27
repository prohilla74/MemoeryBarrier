#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> sharedVariable = 0;

void writerThread() {
    // Write to the shared variable
    sharedVariable.store(42, std::memory_order_relaxed);

    // Memory barrier (synchronize with release semantics)
    std::atomic_thread_fence(std::memory_order_release);
}

void readerThread() {
    // Memory barrier (synchronize with acquire semantics)
    std::atomic_thread_fence(std::memory_order_acquire);

    // Read the shared variable
    int value = sharedVariable.load(std::memory_order_relaxed);

    std::cout << "Value read from sharedVariable: " << value << std::endl;
}

int main() {
    std::thread writer(writerThread);
    std::thread reader(readerThread);

    writer.join();
    reader.join();

    return 0;
}
