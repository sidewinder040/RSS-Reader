#pragma once
#include <string>

class Feed
{
public:
    enum EnumScore
    {
        UNSCORED = 0, // Feed has not been scored
        Low = 1,
        Medium = 2,
        High = 3
    };
private:
    std::string FeedUrl; // URL of the RSS feed
    // EnumScore FeedScore; // Score of the feed (Low, Medium, High)
public:
    Feed(/* args */);

    std::string FeedName; // Name of the feed
    Feed(std::string feedUrl, std::string name, EnumScore feedScore = UNSCORED)
        : FeedUrl(feedUrl), FeedName(name), FeedScore(feedScore) { } // Constructor to initialize the feed URL

    ~Feed() { }
    std::string GetFeedUrl() const { return FeedUrl; } // Get the feed URL
    EnumScore FeedScore; // Score of the feed (Low, Medium, High)
    void SetFeedScore(EnumScore score); // Set the feed score
};




