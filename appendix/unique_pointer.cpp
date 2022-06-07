#include <memory>

int main(void) {
  std::unique_ptr<double[]> a(new double[2]);

  // Initialize the values
  a[0] = 1;
  a[1] = 2;

  // Generate a copy of the array a
  // std::unique_ptr<double[]>b(a);

  // Generate a copy of the array a
  std ::unique_ptr<double[]> b(std ::move(a));

  return EXIT_SUCCESS;
}
