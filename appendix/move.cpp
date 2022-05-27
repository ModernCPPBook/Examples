#include <string>
#include <vector>
#include <iostream>

int main(void){

std::string name = "Parallel C++";
std::vector<std::string> values;

// Copy the object name to the end of the vector
values.push_back(name);


std::cout << "The content of name after copying is " << name << std::endl; 

// Move the object name to the end of the vector
values.push_back(std::move(name));

std::cout << "The content of name after moving is " << name << std::endl; 


}
