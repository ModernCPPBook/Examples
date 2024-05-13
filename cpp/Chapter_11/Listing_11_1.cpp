#define USE_HPX 1
#ifdef USE_HPX
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <coroutine>
namespace par = hpx;
#else
#include <future>
namespace par = std;
#endif
#include <functional>
#include <iostream>

int fib1(int n) {
  if(n < 2) return n;
  par::future<int> f1 = par::async(par::launch::async,fib1,n-1);
  auto f2 = fib1(n-2);
  return f1.get() + f2;
}

#ifdef USE_HPX
par::future<int> fib2(int n) {
  if(n < 2) return par::make_ready_future(n);
  par::future<int> f1 = par::async(par::launch::async,fib2,n-1);
  auto f2 = fib2(n-2);
  return par::dataflow([](auto f1_,auto f2_){
    return f1_.get() + f2_.get();
  }, f1, f2);
}

par::future<int> fib3(int n) { 
  if(n < 2) co_return n;
  auto f1 = par::async(fib3,n-1);
  auto f2 = fib3(n-2);
  co_return (co_await f1) + (co_await f2);
}
#endif

void test_fib(int n,std::function<int(int)> f) {
  auto start_time = std::chrono::high_resolution_clock::now ();
  int r = f(n);
  auto stop_time = std::chrono::high_resolution_clock::now ();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
  std::cout << "fib(" << n << ")=" << r << " time=" << (duration.count()*1e-9) << " secs" << std::endl;
}

int main() {
  for(int i=0;i<20;i++) {
    test_fib(i, fib1);
    #ifdef USE_HPX
    test_fib(i, [](int n)->int { return fib2(n).get(); });
    test_fib(i, [](int n)->int { return fib3(n).get(); });
    #endif
    std::cout << std::endl;
  }
  return 0;
}
