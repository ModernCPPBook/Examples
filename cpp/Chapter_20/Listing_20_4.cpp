#include <algorithm>
#include <iostream>
#include <vector>
//-----------------------------------------------------------------

int main() {
  // Vector to be printed
  std::vector<int> v = {1,2,3,4,5};

  // Print the first element without a leading commas symbol
  std::for_each(v.begin(),v.end(),
    [init = true] (int x) mutable {
     if (init) { std::cout << x; init = false; }
     else { std::cout << ',' << x; }
  });
}
