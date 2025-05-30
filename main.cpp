#include<iostream>
#include "rss-reader.h"
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/format.h>

// ANSI escape codes for colors
// constexpr const char* RED = "\033[31m";
// constexpr const char* GREEN = "\033[32m";
constexpr const char* BLUE = "\033[34m";
constexpr const char* RESET = "\033[0m";

void ListAvailableFeeds(const RSSReader& rssReader);

int main()
{
    std::cout << "RSS-Reader Prototype" << std::endl;
    std::cout << "====================" << std::endl;

    // Add some Feed objects to the RSSReader
    RSSReader rssReader;
    rssReader.AddFeed(Feed("https://techcrunch.com/feed/", "Techcrunch"));
    rssReader.AddFeed(Feed("https://www.wired.com/feed/rss",  "Wired Top Stories"));
    rssReader.AddFeed(Feed("http://feeds.windowscentral.com/wmexperts", "Windows Central"));
    rssReader.AddFeed(Feed("https://www.bleepingcomputer.com/feed/", "Bleeping Computer"));
    rssReader.AddFeed(Feed("https://www.cnet.com/rss/news/", "CNET News"));
    rssReader.AddFeed(Feed("https://www.zdnet.com/news/rss.xml", "ZDNet News"));
    rssReader.AddFeed(Feed("https://feeds.macrumors.com/MacRumors-All", "Mac Rumors"));
    rssReader.AddFeed(Feed("https://www.theverge.com/rss/index.xml", "The Verge"));
    rssReader.AddFeed(Feed("https://www.engadget.com/rss.xml", "Engadget"));
    rssReader.AddFeed(Feed("https://www.techradar.com/rss", "TechRadar"));
    rssReader.AddFeed(Feed("https://www.tomshardware.com/feeds/all", "Tom's Hardware"));
    rssReader.AddFeed(Feed("https://www.thurrott.com/blog/rss", "Thurrott Blog"));
    // Display the available feeds
    std::cout << "Available Feeds:" << std::endl;
    ListAvailableFeeds(rssReader);
    // Prompt the user to select a feed
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Select a feed to fetch (1-" << rssReader.getAvailableFeeds().size() << "): ";
    int feedIndex;
    std::cin >> feedIndex;
    // Validate the feed index
    if (feedIndex < 1 || feedIndex > (int)rssReader.getAvailableFeeds().size()) {
        std::cout << "Invalid feed index. Using default feed URL." << std::endl;
        feedIndex = 1; // Default to the first feed if index is invalid
    }
    std::cout << "Fetching RSS feed..." << std::endl;
    // RSSReader reader("Techchrunch", "https://techcrunch.com/feed/");

    /*** Disabled Feed Fetch and Display ***/
    // Show chosen feed URL
    std::string chosenUrl = rssReader.getAvailableFeeds()[feedIndex - 1].GetFeedUrl();
    std::string chosenName = rssReader.getAvailableFeeds()[feedIndex - 1].FeedName;
    std::cout << "Display Feed: " << chosenName << " (" << chosenUrl << ")" << std::endl;
    rssReader.FetchFeed(feedIndex -1); // Fetch the feed using the first feed URL
    rssReader.displayFeedItems();
    // Uncomment the following lines to enable feed removal and addition tests
    // std::cout << "Test removing a feed..." << std::endl;
    // rssReader.RemoveFeed(chosenName); // Remove the chosen feed
    // std::cout << "Available Feeds after removal:" << std::endl;
    // ListAvailableFeeds(rssReader); // List available feeds after removal

    // // Test adding a new feed
    // std::cout << "Adding a new feed..." << std::endl;
    // rssReader.AddFeed(Feed("https://www.example.com/rss", "Example Feed"));
    // std::cout << "Available Feeds after adding a new feed:" << std::endl;
    // ListAvailableFeeds(rssReader); // List available feeds after adding a new feed
    return 0;
}

void ListAvailableFeeds(const RSSReader& rssReader) {
    int index = 1; // Index for displaying feeds
    for (const auto& feed : rssReader.getAvailableFeeds()) {
        // Assuming feeds are indexed starting from 1
        fmt::print(fmt::emphasis::bold, "[{}] ", index);
        fmt::print(fmt::emphasis::bold, "Feed Name:{}\t", feed.FeedName);
        fmt::print(fmt::emphasis::underline | fmt::emphasis::bold, "{}Feed URL:{}\n{}", BLUE, feed.GetFeedUrl(), RESET);
        index++;
    }
}