#include <string>


class Feed
{
private:
    std::string FeedUrl; // URL of the RSS feed
    enum EnumScore
    {
        Low = 1,
        Medium = 2,
        High = 3
    };
    EnumScore FeedScore; // Score of the feed (Low, Medium, High)
public:
    Feed(/* args */);

    std::string FeedName; // Name of the feed
    Feed(const std::string& feedUrl, const std::string& name)
        : FeedUrl(feedUrl), FeedName(name) { } // Constructor to initialize the feed URL
    
    ~Feed() { }

    void SetFeedScore(EnumScore score); // Set the feed score

};




