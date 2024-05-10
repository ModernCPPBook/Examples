#include <thread>
#include <mutex>
#include <iostream>
//-----------------------------------------------------------------
int main() {
    std::mutex locka, lockb;
    std::thread ta([&](){
        locka.lock();
        std::cout << "Got lock A" << std::endl;
        lockb.lock();
        std::cout << "Got lock A then B" << std::endl;
        lockb.unlock();
        locka.unlock();
    });
    std::thread tb([&](){
        lockb.lock();
        std::cout << "Got lock B" << std::endl;
        locka.lock();
        std::cout << "Got lock B then A" << std::endl;
        locka.unlock();
        lockb.unlock();
    });
    ta.join();
    tb.join();
    return 0;
}
