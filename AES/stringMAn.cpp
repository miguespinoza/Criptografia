#include <iostream>
#include <cstring>
#include <bitset>
#include "AESclass.cpp"
#include <fstream>

int main(int argc, char const *argv[])
{
	if (argc > 1)
  {
    std::string arg1(argv[1]);
    // do stuff with arg1
    cout<<arg1;
  }
	return 0;
}