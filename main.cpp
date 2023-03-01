#include <iostream>

#include <thread>
#include <chrono>
#include <unistd.h>

bool chopping = true;

void cpu_waster() {
    printf("CPU Waster Process:  %d\n", _getpid());
    printf("CPU Waster Process:  %d\n", std::this_thread::get_id());
    while(true) continue;
}

void vegetable_chopper(const char* name) {
    unsigned int vegetable_count = 0;
    while(chopping) {
        vegetable_count++;
    }

    printf("%s chopped %u vegetables.\n", name, vegetable_count);
}


int main() {
    printf("Main process id %d\n", _getpid());
    printf("Main process id %d\n", std::this_thread::get_id());
    std::thread thread1(cpu_waster);
    std::thread thread2(cpu_waster);

    std::thread olivia(vegetable_chopper, "Olivia");
    std::thread barron(vegetable_chopper, "Barron");

    printf("barron and olivia are chopping vegetables...\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    chopping = false;
    barron.join();
    olivia.join();

    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}

