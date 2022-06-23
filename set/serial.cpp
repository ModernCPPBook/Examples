#include "config.h"
#include <pbm.hpp>

// Defintion of utility
PBM pbm = PBM(size_x, size_y);

// Function to smoothen the coloring
std::tuple<size_t, size_t, size_t> get_rgb(int value) {
  double t = double(value) / double(max_iteration);
  int r = (int)(9 * (1 - t) * t * t * t * 255);
  int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
  int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

  return std::make_tuple(r, g, b);
}

// Kernel to compute the Mandeklbrot set
size_t mandelbrot(complex c){
   std::complex<double> z(0, 0); 
for (size_t i = 0; i < max_iteration; i++) {
z = z * z + c;
 if (abs(z) > 2.0) {
      return i;

}
}
	return  0;
  
}

// Function to comoute the Mandelbrot set for a pixel
size_t compute_pixel(complex c) {
  std::complex<double> z(0, 0);
  for (size_t i = 0; i < max_iteration; i++) {
    if (type == 'm')
	  return mandelbrot(c);
    //else 
//        z = julia(c);
    }
  
  return 0;
}

int main(void) {
  for (size_t i = 0; i < size_x; i++) {
    // Compute c for z^2 < c
    complex c =
        complex(0, 4) * complex(i, 0) / complex(size_x, 0) - complex(0, 2);

    for (size_t j = 0; j < size_y; j++) {
      // Get the number of iterations
      int value = compute_pixel(c + 4.0 * j / size_y - 2.0);
      // Convert the smoothened value to RGB color space
      std::tuple<size_t, size_t, size_t> color = get_rgb(value);
      // Set the pixel color
      pbm(i, j) = make_color(std::get<0>(color), std::get<1>(color),
                             std::get<2>(color));
    }
  }

  // Save the image
  pbm.save("image_serial.pbm");

  return EXIT_SUCCESS;
}
