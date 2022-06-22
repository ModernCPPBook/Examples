#include <iostream>

int main(void){

double sum = 0 ;
size_t count = 0;
double x = 0;

while (std::cin >> x)  
{
	sum += x;
	++count;
}

std::cout << "Average: " << sum /count << std::endl; 

return EXIT_SUCCESS;
}
