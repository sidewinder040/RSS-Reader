#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "rss-reader.h"

constexpr const char* FEED_FILE = "feeds.txt"; // File to save feeds

// ANSI escape codes for colors
// constexpr const char* RED = "\033[31m";
// constexpr const char* GREEN = "\033[32m";
constexpr const char* BLUE = "\033[34m";
constexpr const char* RESET = "\033[0m";

void ListAvailableFeeds(const RSSReader& rssReader);

int main(int argc, char** argv)
{
    bool list = false;
    int show_index = -1;
    std::vector<std::string> add_args;
    int delete_index = -1;
    bool show_version = false;
    bool show_help = false;

    // Simple manual argument parsing
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-l" || arg == "--list") list = true;
        else if ((arg == "-s" || arg == "--show") && i + 1 < argc) show_index = std::stoi(argv[++i]);
        else if ((arg == "-a" || arg == "--add") && i + 2 < argc) {
            add_args.push_back(argv[++i]);
            add_args.push_back(argv[++i]);
        }
        else if ((arg == "-d" || arg == "--delete") && i + 1 < argc) delete_index = std::stoi(argv[++i]);
        else if (arg == "-v" || arg == "--version") show_version = true;
        else if (arg == "-h" || arg == "--help") show_help = true;
    }

    RSSReader rssReader;
    rssReader.LoadFeedsFromFile(FEED_FILE);
    if (rssReader.getAvailableFeeds().empty()) {
        rssReader.AddFeed(Feed("https://techcrunch.com/feed/", "TechCrunch"));
    }

    if (list) {
        std::cout << "Available Feeds:" << std::endl;
        ListAvailableFeeds(rssReader);
        return 0;
    }
    if (show_index > 0) {
        int feedIndex = show_index;
        if (feedIndex < 1 || feedIndex > (int)rssReader.getAvailableFeeds().size()) {
            std::cout << "Invalid feed index." << std::endl;
            return 1;
        }
        std::string chosenUrl = rssReader.getAvailableFeeds()[feedIndex - 1].GetFeedUrl();
        std::string chosenName = rssReader.getAvailableFeeds()[feedIndex - 1].FeedName;
        std::cout << "Display Feed: " << chosenName << " (" << chosenUrl << ")" << std::endl;
        rssReader.FetchFeed(feedIndex - 1);
        rssReader.displayFeedItems();
        return 0;
    }
    if (!add_args.empty()) {
        rssReader.AddFeed(Feed(add_args[1], add_args[0]));
        rssReader.SaveFeedsToFile(FEED_FILE, rssReader.getAvailableFeeds());
        std::cout << "Feed added: " << add_args[0] << " (" << add_args[1] << ")" << std::endl;
        return 0;
    }
    if (delete_index > 0) {
        int feedIndex = delete_index;
        if (feedIndex < 1 || feedIndex > (int)rssReader.getAvailableFeeds().size()) {
            std::cout << "Invalid feed index." << std::endl;
            return 1;
        }
        std::string feedName = rssReader.getAvailableFeeds()[feedIndex - 1].FeedName;
        rssReader.RemoveFeed(feedName);
        rssReader.SaveFeedsToFile(FEED_FILE, rssReader.getAvailableFeeds());
        std::cout << "Feed deleted: " << feedName << std::endl;
        return 0;
    }
    if (show_version) {
        std::cout << "RSS-Reader version 1.0.0" << std::endl;
        return 0;
    }
    if (show_help || argc == 1) {
        std::cout << "Usage: rss-reader [OPTIONS]\n"
                  << "  -l, --list                List available feeds\n"
                  << "  -s, --show <index>        Show all news items in the selected feed\n"
                  << "  -a, --add <name> <url>    Add a new feed\n"
                  << "  -d, --delete <index>      Delete a feed by index\n"
                  << "  -h, --help                Show this help message\n"
                  << "  -v, --version             Show application version\n";
        return 0;
    }
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
