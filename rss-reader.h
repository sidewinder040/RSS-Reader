#pragma once
#include <string>
#include <iostream>

class RSSReader {
public:
    // Constructor
    RSSReader(const std::string& feedUrl);
    
    // Method to fetch and parse the RSS feed
    void fetchFeed();

    // Method to display the feed items
    void displayFeedItems() const;
};