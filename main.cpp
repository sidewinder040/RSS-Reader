#include<iostream>
#include "rss-reader.h"

int main()
{
    std::cout << "RSS-Reader Prototype" << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << "Fetching RSS feed..." << std::endl;
    RSSReader reader("https://example.com/rss");
    reader.FetchFeed();
    std::cout << "Parsing RSS feed..." << std::endl;
    reader.displayFeedItems();
    std::cout << "RSS feed fetched and displayed." << std::endl;
    return 0;
}
