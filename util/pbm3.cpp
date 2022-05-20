//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <vector>
#include <complex>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "pbm.hpp"

/// For debugging, print out a vector of int's
std::ostream& operator<<(std::ostream& o,const std::vector<int>& v) {
    o << "[";
    for(int i=0;i<v.size();i++) {
        if(i > 0) o << ", ";
        o << v[i];
    }
    return o << "]";
}

const double pi = 4.0*atan(1.0);

const int max_iter = 255;

// Used to initialize Julia sets
double values[2] = {0, 0};

typedef std::complex<double> creal;

// Mandelbrot pixel creator
int pixel1(creal c) {
    creal z(0,0);
    for(int i=0;i<max_iter;i++) {
        z = z*z + c;
        if(abs(z) > 2.0) {
            return i;
        }
    }
    return max_iter;
}

// Julia pixel creator
int pixel2(creal z) {

    // If you want to play around and
    // make interesting images, change
    // this constant.
    // creal c(-0.4,.6);
    creal c(values[0], values[1]);
    
    for(int i=0;i<max_iter;i++) {
        z = z*z + c;
        if(abs(z) > 2.0) {
            return i;
        }
    }
    return max_iter;
}

const int sz = 1024*4;
int work_to_be_done = sz;
extern int work_to_be_done;

// Create a pbm image object
PBM p(sz, sz);

int (*pixel)(creal c) = pixel1;

// Create a row of the Mandelbrot/Julia set
void create_result(int row,std::vector<int>& result) {
    int h = p.height();
    int w = p.width();
    creal c = creal(0,4)*creal(row,0)/creal(h,0)-creal(0,2);
    static bool init = true;
    if(init) {
        init = false;
        const char *val1 = getenv("VAL1");
        if(val1 != nullptr) {
            values[0] = std::stod(val1);
            pixel = pixel2;
        }
        const char *val2 = getenv("VAL2");
        if(val2 != nullptr) {
            values[1] = std::stod(val2);
            pixel = pixel2;
        }
    }
    for(int i=0;i<w;i++) {
        int r=0, g=0, b=0;
        
        // Use either pixel1 or pixel2 here depending
        // on what you want.
        int iters = pixel(c + 4.0*i/w - 2.0);
        
        // Map an integer to a color
        r = (max_color-1)*sin(iters*pi/max_iter);
        g = r/2; //(max_color-1)*cos(iters*pi*.5/max_iter);
        b = (max_color-1)*cos(0.5*pi-iters*pi*.5/max_iter);
        
        result.push_back(make_color(r,g,b));
    }
}

void apply_result(int row_index,const std::vector<int>& result) {
    p.row(row_index) = result;
}

void finish_up() {
    p.save("image.pbm");
}
