#include "rss-reader.h"

RSSReader::RSSReader(const std::string& feedUrl) {
    // Constructor implementation
   std::cout << "RSSReader initialized with feed URL: " << feedUrl << std::endl;
}

void RSSReader::displayFeedItems() const {
    std::cout << "Displaying feed items..." << std::endl;
    // Here you would typically iterate over the parsed feed items and display them
    // For demonstration, we'll just print a placeholder message
    std::cout << "Feed item 1: Example Item 1" << std::endl;
    std::cout << "Feed item 2: Example Item 2" << std::endl;
    std::cout << "Feed item 3: Example Item 3" << std::endl;
    // In a real implementation, you would replace the above with actual feed item data
    // For example, you might have a vector of feed items and iterate over it:
    // for (const auto& item : feedItems) {
    //     std::cout << "Feed item: " << item.title << std::endl;
    // }
}