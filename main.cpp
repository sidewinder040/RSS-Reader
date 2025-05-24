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

    // Add some Feed objects to the RSSReader
    RSSReader rssReader;
    rssReader.AddFeed(Feed("https://techcrunch.com/feed/", "Techcrunch"));
    rssReader.AddFeed(Feed("https://www.wired.com/feed/rss",  "Wired Top Stories"));
    rssReader.AddFeed(Feed("http://feeds.windowscentral.com/wmexperts", "Windows Central"));

    std::cout << "Fetching RSS feed..." << std::endl;
    // RSSReader reader("Techchrunch", "https://techcrunch.com/feed/");
    rssReader.FetchFeed(2); // Fetch the feed using the first feed URL
    std::cout << "Parsing RSS feed..." << std::endl;
    rssReader.displayFeedItems();
    std::cout << "RSS feed fetched and displayed." << std::endl;
    
    // fmt underline and color blue
    fmt::print(fmt::emphasis::underline | fmt::emphasis::bold, "{}https://www.google.com\n{}", BLUE, RESET);
    return 0;
}
