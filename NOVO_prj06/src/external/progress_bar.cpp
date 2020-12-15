#include "progress_bar.hpp"

#include <chrono> 
#include <ctime> 
#include <iostream> 
  
using namespace std; 
  
void progressbar(int progress, const std::string& pos_msg) {
    // std::cout << '\r';
     auto timenow = 
      std::chrono::system_clock::to_time_t(chrono::system_clock::now());

    progress++;
    const int progress_stages = 10;
    if (progress > progress_stages) progress = progress_stages;
    std::cout << "[";
    for (int i = 0;i <= progress_stages-1;i++)
        if (i < progress)
            std::cout << '=';
        else
            std::cout << ' ';
    std::cout << "] " << pos_msg << " " << progress << "0 % " << " at " << ctime(&timenow);
    std::cout.flush();
}

void progressbar_finish() {
    std::cout << std::endl;
}