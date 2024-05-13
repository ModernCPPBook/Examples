#include <fstream> 
#include <iostream>
#include <pbm.hpp> 
//-----------------------------------------------------------------
std::tuple<int, std::vector<int>> split(std::string line) { 

  std::istringstream stream(line); 
  std::string index;
  std::vector<int> row;

  std::string s;
  bool first = true;
  while (getline(stream, s, ' ')) { 
    if (first) {
      index = s;
      first = false;
    } else
      row.push_back(std::stoi(s));
  }
  return std::make_tuple(std::stoi(index), row);
}

int main(int argc, char **argv) {

  PBM pbm = PBM(size_y, size_x); 

  size_t id = 0;

  while (true) {  

    std::ifstream file; 
    file.open("data_" + std::to_string(id) + ".part");
    if(!file.good()) {
        std::cout << "Files read: " << id << std::endl;
        break;
    }

    int index; 
    std::vector<int> row; 

    std::string s;
    while (std::getline(file, s)) { 

      auto res = split(s);  

      index = std::get<0>(res); 
      row = std::get<1>(res); 
      pbm.row(index) = row; 
    }
    id++;
  }

  pbm.save("image_combined.pbm"); 

  return 0;
}
