#pragma once
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <string>
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include "tinyxml2.h"
#include <vector>
#include <algorithm>
#include "feed.h"
#include "feed-item.h"

class RSSReader {
public:
    // Constructors
    // Default constructor
    RSSReader();
    RSSReader(const std::string& feedName, const std::string& feedUrl);
    
    // Method to fetch and parse the RSS feed
    void FetchFeed(int feedIndex = 0); // Default to the first feed if no index is provided

    // Method to get available feeds
    std::vector<Feed> getAvailableFeeds() const { return feeds; }

    // Method to display the feed items
    void displayFeedItems() const;

    void AddFeed(const Feed& feed);
    void RemoveFeed(const std::string& feedUrl);
    void RemoveFeedByIndex(int index);

    // Methods for saving and loading feeds
    void SaveFeedsToFile(const std::string& filename, const std::vector<Feed> &feeds);
    void LoadFeedsFromFile(const std::string& filenam);
    
private:
    std::string feedUrl; // URL of the RSS feed
    std::vector<Feed> feeds; // Vector to store feed objects
    std::vector<feed_item> feedItems; // Vector to store feed items
    tinyxml2::XMLDocument doc; // XML document object for parsing

    // ANSI escape codes for colors
    const char* RED = "\033[31m";
    // constexpr const char* GREEN = "\033[32m";
    const char* BLUE = "\033[34m";
    const char* RESET = "\033[0m";

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
};