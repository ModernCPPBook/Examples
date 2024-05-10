#include <thread>
#include <iostream>
//-----------------------------------------------------------------
double sum = 0;
const int sz = 40;
double* data = new double[sz];

void update(int n) {
    for(int i=0;i<sz;i++) {
        sum += data[i];
        std::cout << "working sum=" << sum << " at step=" << i << std::endl;
    }
}

int main() {
    for(int i=0;i<sz;i++) data[i] = 1.0;
    std::thread t1(update,1), t2(update,2);
    t1.join(); t2.join();
    std::cout << "final sum=" << sum << std::endl;
    return 0;
}
