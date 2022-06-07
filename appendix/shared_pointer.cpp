#include <iostream>
#include <memory>

int main(void) {
  // Generate a unique pointer of a double array
  std ::shared_ptr<double[]> a(new double[2]);

  // Initialize the value
  a[0] = 1;
  a[1] = 2;

  // Generate a copy of the array a
  std ::shared_ptr<double[]> b(a);

  // Print the total referenxes to the array
  std::cout << a.use_count() << std::endl;

  // Release the smart pointer b
  b.reset();

  // Print the total referenxes to the array
  std::cout << a.use_count() << std::endl;

  // Generate a copy of the array a
  // std :: unique_ptr < double [] > b ( a ) ;

  return EXIT_SUCCESS;
}
