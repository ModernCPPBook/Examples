//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef PBM_HPP
#define PBM_HPP

// Header for generating PBM image files
// https://en.wikipedia.org/wiki/Netpbm

#include <fstream>
#include <vector>

const int max_color = 256;

// convert an rgb tuple to an int
int make_color(int r,int g,int b) {
    assert(0 <= r && r < max_color);
    assert(0 <= g && g < max_color);
    assert(0 <= b && b < max_color);
    return (b*max_color+g)*max_color+r;
}

class PBM {
    // width and height
    int w, h;
    // a vector of vector if ints to store the pixels
    std::vector<std::vector<int>> values;
public:

    int width() { return w; }
    
    int height() { return h; }
    
    PBM(int w_, int h_) : w(w_), h(h_) {
        // initialize vector to all zeros
        for(int j=0;j<h;j++) {
            std::vector<int> row;
            for(int i=0;i<w;i++) {
                row.push_back(0);
            }
            values.push_back(std::move(row));
        }
    }
    ~PBM() { }
    
    // get or set a pixel at i, j
    int& operator()(int i,int j) {
        return values.at(j).at(i);
    }
    
    // get or set a row at j
    std::vector<int>& row(int j) {
        return values.at(j);
    }
    
    // save to a file
    void save(const char *fname) {
        std::ofstream f(fname);
        f << "P3\n";
        f << w << " " << h << "\n";
        f << "255\n";
        const int mv = 256;
        for(int j=0;j<h;j++) {
            auto& row = values.at(j);
            for(int i=0;i<w;i++) {
                int color = row.at(i);
                for(int c=0;c < 3;c++) {
                    f << (color % max_color) << " ";
                    color /= max_color;
                }
                f << "\n";
            }
        }
        f.close();
    }
};
#endif