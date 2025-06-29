#include "main.hpp"

constexpr const char* FEED_FILE = "/Users/markcrouch/.config/rss-reader/feeds.txt"; // File to save feeds

// ANSI escape codes for colors
// constexpr const char* RED = "\033[31m";
// constexpr const char* GREEN = "\033[32m";
constexpr const char* BLUE = "\033[34m";
constexpr const char* RESET = "\033[0m";

// void ListAvailableFeeds(const RSSReader& rssReader);

int main(int argc, char** argv)
{
    bool list = false;
    int show_index = -1;
    std::vector<std::string> add_args;
    int delete_index = -1;
    bool show_version = false;
    bool show_help = false;
    int rate_index = -1;
    int rate_value = -1;

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
        else if ((arg == "-r" || arg == "--rate") && i + 2 < argc) {
            rate_index = std::stoi(argv[++i]);
            rate_value = std::stoi(argv[++i]);
        }
        else if (arg == "-v" || arg == "--version") show_version = true;
        else if (arg == "-h" || arg == "--help") show_help = true;
    }

    RSSReader rssReader;
    rssReader.LoadFeedsFromFile(FEED_FILE);
    // std::vector<Feed> feeds = rssReader.getAvailableFeeds();
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
    if (rate_index > 0 && rate_value > 0) {
        int feedIndex = rate_index;
        if (feedIndex < 1 || feedIndex > (int)rssReader.getAvailableFeeds().size()) {
            std::cout << "Invalid feed index." << std::endl;
            return 1;
        }
        if (rate_value < 1 || rate_value > 3) {
            std::cout << "Invalid rating value. Use 1 (Low), 2 (Medium), or 3 (High)." << std::endl;
            return 1;
        }
        // Get feeds, set score, and save
        auto feeds = rssReader.getAvailableFeeds();
        feeds[feedIndex - 1].SetFeedScore(static_cast<Feed::EnumScore>(rate_value));
        rssReader.SaveFeedsToFile(FEED_FILE, feeds);
        std::cout << "Feed '" << feeds[feedIndex - 1].FeedName << "' rated as " << rate_value << std::endl;
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
                  << "  -r, --rate <index> <rating>  Rate a feed (1=Low, 2=Medium, 3=High)\n"
                  << "  -h, --help                Show this help message\n"
                  << "  -v, --version             Show application version\n";
        return 0;
    }
    // rssReader.SaveFeedsToFile(FEED_FILE, rssReader.getAvailableFeeds());
    return 0;
}

void ListAvailableFeeds(const RSSReader& rssReader) {
    int index = 1; // Index for displaying feeds
    for (const auto& feed : rssReader.getAvailableFeeds()) {
        // Assuming feeds are indexed starting from 1
        fmt::print(fmt::emphasis::bold, "[{}] ", index);
        fmt::print(fmt::emphasis::bold, "Feed Name:{}\t", feed.FeedName);
        fmt::print(fmt::emphasis::underline | fmt::emphasis::bold, "{}Feed URL:{}{}\t", BLUE, feed.GetFeedUrl(), RESET);
        // Display feed score if available with user frienncdly unum text
        if (feed.FeedScore != Feed::UNSCORED) {
            std::string scoreText;
            switch (feed.FeedScore) {
                case Feed::Low: scoreText = "Low"; break;
                case Feed::Medium: scoreText = "Medium"; break;
                case Feed::High: scoreText = "High"; break;
                default: scoreText = "Unscored"; break;
            }
            fmt::print(fmt::emphasis::bold, "Score: {}\n", scoreText);
        } else {
            fmt::print(fmt::emphasis::bold, "Score: Unscored\n");
        }
        
        index++;
    }
}
