#include <list>
#include <iostream>
//-----------------------------------------------------------------
int main() {
  std::list<int> values = {2, 7, 3, 9, 1};

  // Accessing the iterator to the first element
  std::list<int>::iterator it = std::begin(values); 

  for (; it != std::end(values); it++)  
    // Accessing the element using the dereference operator *
    std::cout << *it << std::endl; 

  std::cout << "------" << std::endl;

  for (const int value : values) {  
    std::cout << value << std::endl;
  }

  std::cout << "------" << std::endl;

  for (int index = 0; const int value : values) {  
    std::cout << "Index=" << index << " Value= " << value
              << std::endl;
  }
}
