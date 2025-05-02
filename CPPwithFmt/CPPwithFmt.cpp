#include <iostream>
#include <string>

// fmt library requires UTF-8. Configure msbuild compiler for this by modifying the project settings:
// Configuration Properties > C/C++ > Command Line -> Additional Options -> Add `/utf-8`
#include <fmt/core.h>

// rapidfuzz requires AT LEAST C++ 17. Configure C++ language version by going to:
// Project > Configuration Properties > General > C++ Language Standard > ISO C+ +17 Standard (/std:c++ 17)
#include <rapidfuzz/fuzz.hpp>  // Docs: https://github.com/rapidfuzz/rapidfuzz-cpp?tab=readme-ov-file#usage


int main()
{
    std::string name = "Elyasaf";  // std::string is utf-8 (BTW, std::wstring utf-16)
    fmt::print("Hello {} from the fmt library! 👋\n", name);

    std::string str1 = "Hello world!";
    std::string str2 = "Hello rapidfuzz!";
    
    double simpleRatio = rapidfuzz::fuzz::ratio(str1, str2);
    double partialRatio = rapidfuzz::fuzz::partial_ratio(str1, str2);
    double tokenSetRatio = rapidfuzz::fuzz::token_set_ratio(str1, str2);
    double tokenSortRatio = rapidfuzz::fuzz::token_sort_ratio(str1, str2);
    
    fmt::print(
        "\nrapidfuzz metrics between:\n> \"{}\"\n> \"{}\"\n",
        str1,
        str2
    );

    fmt::print("| {:^14} | {:<5.5} |\n", "simpleRatio", simpleRatio);
    fmt::print("| {:^14} | {:<5.5} |\n", "partialRatio", partialRatio);
    fmt::print("| {:^14} | {:<5.5} |\n", "tokenSetRatio", tokenSetRatio);
    fmt::print("| {:^14} | {:<5.5} |\n", "tokenSortRatio", tokenSortRatio);
    return 0;
}
