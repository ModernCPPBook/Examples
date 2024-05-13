#include <thread>
#include <iostream>
#include <mutex>
//-----------------------------------------------------------------
double sum = 0;
const int sz = 1000000;
double* data = new double[sz];

std::mutex m;

void update(int n) {
    for(int i=0;i<sz;i++) {
        m.lock();
        sum += data[i];
        m.unlock();
    }
}

int main() {
    for(int i=0;i<sz;i++) data[i] = 1.0;
    std::thread t1(update,1), t2(update,2);
    t1.join(); t2.join();
    std::cout << "final sum=" << sum << std::endl;
    return 0;
}
