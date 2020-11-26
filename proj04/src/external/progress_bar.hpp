#ifndef PROGRESS_BAR_HPP
#define PROGRESS_BAR_HPP

#include <iostream>
#include <string>

/** adapted from https://www.quora.com/How-do-I-create-a-progress-bar-in-C++?share=1
* creates a progress bar; use [pos_msg] to put a msg after the percentage
* ex.:
* [==         ] 20 % pos_msg
*  [===========] 100 %
*/
void progressbar(int progress, const std::string& pos_msg);

void progressbar_finish();

#endif