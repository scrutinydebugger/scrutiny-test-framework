#include "scrutinytest/scrutinytest.hpp"

#include <iostream>
int main(int argc, char *argv[])
{
    scrutinytest::set_ostream(&std::cout);
    return scrutinytest::main();
}