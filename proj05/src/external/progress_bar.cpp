#include "progress_bar.hpp"

void progressbar(int progress, const std::string& pos_msg) {
    progress++;
    const int progress_stages = 10;
    if (progress > progress_stages) progress = progress_stages;
    std::cout << "[";
    for (int i = 0;i <= progress_stages-1;i++)
        if (i < progress)
            std::cout << '=';
        else
            std::cout << ' ';
    std::cout << "] " << progress << "0 % " << pos_msg << '\r';
    std::cout.flush();
}

void progressbar_finish() {
    std::cout << std::endl;
}