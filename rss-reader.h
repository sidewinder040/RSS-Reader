#pragma once
#include <string>
#include <iostream>
#include <curl/curl.h>
#include "tinyxml2.h"
#include <vector>
#include "feed.h"
#include "feed-item.h"
#include <fmt/base.h>
#include <fmt/color.h>
#include <fmt/format.h>

class RSSReader {
public:
    // Constructors
    // Default constructor
    RSSReader();
    RSSReader(const std::string& feedName, const std::string& feedUrl);
    
    // Method to fetch and parse the RSS feed
    void FetchFeed();

    // Method to display the feed items
    void displayFeedItems() const;

    void AddFeed(const Feed& feed);
    void RemoveFeed(const std::string& feedUrl);
    
private:
    std::string feedUrl; // URL of the RSS feed
    std::vector<Feed> feeds; // Vector to store feed objects
    std::vector<feed_item> feedItems; // Vector to store feed items
    tinyxml2::XMLDocument doc; // XML document object for parsing
    // CURL* curl; // CURL object for fetching the feed
    // CURLcode res; // Result code from CURL operations

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
};