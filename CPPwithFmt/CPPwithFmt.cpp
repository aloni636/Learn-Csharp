#include <iostream>
#include <fmt/core.h>
#include <string>

// fmt library requires UTF-8. Configure msbuild compiler for this by modifying the project settings:
// Configuration Properties > C/C++ > Command Line -> Additional Options -> Add `/utf-8`

int main()
{
    std::string name = "Elyasaf";  // std::string is utf-8 (BTW, std::wstring utf-16)
    fmt::print("Hello {}! 👋", name);
    return 0;
}
