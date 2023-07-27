#include <atomic>
#include <thread>
#include <iostream>

/*
In computer programming, a memory barrier, also known as a memory fence or memory synchronization barrier,
is a mechanism used to enforce ordering constraints on memory operations performed by multiple threads
or processors.It ensures that memory access operations(e.g., read and write) are properly synchronized 
and do not violate the intended order of execution.

In a multi - threaded environment, threads can access shared memory concurrently, which can lead to
various issues like data races, where multiple threads try to accessand modify shared data simultaneously.
Memory barriers help prevent these issues by establishing a clear order of execution for memory operations.

There are two main types of memory barriers :

Compiler Memory Barriers :
These barriers are specific to the compilerand ensure that the compiler does not reorder memory operations around the barrier.For example, the volatile keyword in C++ is often used to create a compiler memory barrier.
*/

volatile int complier_sharedVariable;

/* The 'volatile' keyword prevents compiler optimizations that could reorder reads / writes to sharedVariable
Hardware Memory Barriers :
These barriers involve CPU instructions that enforce ordering of memory operations at the hardware level.They ensure that memory operations on one processor core become visible to other cores in the correct order.Different processors have different instructions for memory barriers.For instance, on x86, the "MFENCE" instruction serves as a full memory barrier.

Here's a simple example to illustrate how a memory barrier can be used:
*/

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
