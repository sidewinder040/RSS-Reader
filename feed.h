#include <string>


class Feed
{
private:
    std::string FeedUrl; // URL of the RSS feed
    enum EnumScore
    {
        Unscored = 0,
        Low = 1,
        Medium = 2,
        High = 3
    };
    // EnumScore FeedScore; // Score of the feed (Low, Medium, High)
public:
    Feed(/* args */);
    EnumScore FeedScore; // Score of the feed (Low, Medium, High)
    std::string FeedName; // Name of the feed
    Feed(std::string feedUrl, std::string name)
        : FeedUrl(feedUrl), FeedName(name) { FeedScore = Unscored; } // Constructor to initialize the feed URL

    ~Feed() { }
    std::string GetFeedUrl() const { return FeedUrl; } // Get the feed URL
    void SetFeedScore(EnumScore score); // Set the feed score
};




