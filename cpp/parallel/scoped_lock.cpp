#include <thread>
#include <mutex>
#include <iostream>
//-----------------------------------------------------------------
int main() {
    std::mutex locka, lockb;
    std::thread ta([&](){
        std::scoped_lock slock{locka, lockb};
        std::cout << "Got lock A then B" << std::endl;
    });
    std::thread tb([&](){
        std::scoped_lock slock{lockb, locka};
        std::cout << "Got lock B then A" << std::endl;
    });
    ta.join();
    tb.join();
    return 0;
}
