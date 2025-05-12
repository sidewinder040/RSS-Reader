#include<iostream>
#include "rss-reader.h"
#include <fmt/base.h>
#include <fmt/color.h>
#include <fmt/format.h>

// ANSI escape codes for colors
// constexpr const char* RED = "\033[31m";
// constexpr const char* GREEN = "\033[32m";
constexpr const char* BLUE = "\033[34m";
constexpr const char* RESET = "\033[0m";

int main()
{
    std::cout << "RSS-Reader Prototype" << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << "Fetching RSS feed..." << std::endl;
    RSSReader reader("https://techcrunch.com/feed/");
    reader.FetchFeed();
    std::cout << "Parsing RSS feed..." << std::endl;
    reader.displayFeedItems();
    std::cout << "RSS feed fetched and displayed." << std::endl;
    
    // fmt underline and color blue
    fmt::print(fmt::emphasis::underline | fmt::emphasis::bold, "{}http://www.google.com\n{}", BLUE, RESET);
    return 0;
}
