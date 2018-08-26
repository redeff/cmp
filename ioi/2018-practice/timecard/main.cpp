#include "timecard.h"

void init(int n){
    return;
}
std::string convert(std::string s){
    for(char &c : s) c |= 'A' ^ 'a';
    return s;
}
