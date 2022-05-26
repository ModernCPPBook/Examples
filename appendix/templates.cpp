//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <iostream>

// Definition of multiple functions
double add(double a, double b) {
	return a + b;
}

float add(int a, int b) { 
	return a + b;
}

// Function template
template<typename T>
T add_template(T a, T b){ 
	return a+b;
}


int main(void)
{

std::cout << add(1.0,1.5) << std::endl;
std::cout << add(1,2) << std::endl;
std::cout << "---------" << std::endl;
std::cout << add_template<double>(1.0,1.5) << std::endl;
std::cout << add_template<int>(1,2) << std::endl;

return EXIT_SUCCESS;

}
