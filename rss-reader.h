#pragma once
#include <string>
#include <iostream>
#include <curl/curl.h>
#include <tinyxml2.h>
#include <vector>

class RSSReader {
public:
    // Constructor
    RSSReader(const std::string& feedUrl);
    
    // Method to fetch and parse the RSS feed
    void FetchFeed();

    // Method to display the feed items
    void displayFeedItems() const;
private:
    std::string feedUrl; // URL of the RSS feed
    std::vector<std::string> feedItems; // Vector to store feed items
    tinyxml2::XMLDocument doc; // XML document object for parsing
    CURL* curl; // CURL object for fetching the feed
    CURLcode res; // Result code from CURL operations
};