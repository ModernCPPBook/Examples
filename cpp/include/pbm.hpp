#ifndef PBM_HPP
#define PBM_HPP

// Header for generating PBM image files
// https://en.wikipedia.org/wiki/Netpbm

#include <cassert>
#include <fstream>
#include <tuple>
#include <vector>

#include <config.hpp>
//-----------------------------------------------------------------
// Function to smoothen the coloring
std::tuple<size_t, size_t, size_t> get_rgb(int value) {
  double t = double(value) / double(max_iterations);
  int r = (int)(9 * (1 - t) * t * t * t * 255);
  int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
  int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

  return std::make_tuple(r, g, b);
}
// convert an rgb tuple to an int
int make_color(int r, int g, int b) {
  assert(0 <= r && r < max_color);
  assert(0 <= g && g < max_color);
  assert(0 <= b && b < max_color);
  return (b * max_color + g) * max_color + r;
}

template<typename vector_type>
class PBM_ {
  // width and height
  int w, h;
  // a vector of vector if ints to store the pixels
  typename vector_type::allocator_type a;
  vector_type values;

  void _init() {
    // initialize vector to all zero
    for (int j = 0; j < h; j++) {
      std::vector<int> row;
      for (int i = 0; i < w; i++) {
        row.push_back(0);
      }
      values[j] = std::move(row);
    }
  }

 public:
  int width() { return w; }

  int height() { return h; }

  PBM_(){};

  PBM_(int w_, int h_) : w(w_), h(h_), a(), values(h_,a) { _init(); }
  PBM_(int w_, int h_, typename vector_type::allocator_type a_) : w(w_), h(h_), a(a_), values(h_,a) { _init(); }
  ~PBM_() {}

  // get or set a pixel at i, j
  int& operator()(int i, int j) { return values.at(j).at(i); }

  // get or set a row at j
  std::vector<int>& row(int j) { return values.at(j); }

  // save to a file
  void save(const std::string& fname) {
    std::ofstream f(fname);
    f << "P3\n";
    f << w << " " << h << "\n";
    f << max_color-1 << "\n";
    for (int j = 0; j < h; j++) {
      auto& row = values.at(j);
      for (int i = 0; i < w; i++) {
        int color = row.at(i);
        for (int c = 0; c < 3; c++) {
          f << (color % max_color) << " ";
          color /= max_color;
        }
        f << "\n";
      }
    }
    f.close();
  }
};

using PBM = PBM_<std::vector<std::vector<int>>>;
#endif
