/**
 * This is the Parameter class that will hold the user input after it is parsed
 *
 * @author Aaron Bading
 * @date 02/6/22
 * @info Course COP4635
 */

#ifndef Param_H
#define Param_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Param
{
public:

Param();
void printParams();

private:
char* inputRedirect;	/* file name or NULL */

};
#endif
