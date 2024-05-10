#include <thread>
#include <iostream>
#include <mutex>
//-----------------------------------------------------------------
double sum = 0;
const int partial_sz = 1000;
const int sz = partial_sz*partial_sz;
double* data = new double[sz];

std::mutex m;

void update(int n) {
    for(int j=0;j<partial_sz;j++) {
        // Do part of the sum on a local variable, partial_sum
        double partial_sum = 0;
        for(int i=0;i<partial_sz;i++) {
            partial_sum += data[i];
        }
        // update the result using the lock
        m.lock();
        sum += partial_sum;
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
