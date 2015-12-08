#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>

// returns if two doubles are almost equals
bool almost_equals_double(double x, double y, double epsilon = 0.001);

// checks if a string contains any number
bool contains_number(std::string & s);

// generate file
void generateFile(std::string & filename, std::string & content);

#endif
