#include <thread>
#include <iostream>
#include <atomic>
//-----------------------------------------------------------------
std::atomic<double> sum = 0;
const int partial_sz = 1000;
const int sz = partial_sz*partial_sz;
double* data = new double[sz];

void update(int n) {
    for(int j=0;j<partial_sz;j++) {
        // Do part of the sum on a local variable, partial_sum
        double partial_sum = 0;
        for(int i=0;i<partial_sz;i++) {
            partial_sum += data[i];
        }
        while(true) {
            double expected = sum.load();
            double desired = expected + partial_sum;
            // try update, if success break
            if(sum.compare_exchange_strong(expected, desired))
                break;
        }
    }
}

int main() {
    for(int i=0;i<sz;i++) data[i] = 1.0;
    std::thread t1(update,1), t2(update,2);
    t1.join(); t2.join();
    std::cout << "final sum=" << sum << std::endl;
    return 0;
}
