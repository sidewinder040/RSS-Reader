#include <string>


class Feed
{
private:
    std::string FeedUrl; // URL of the RSS feed
    enum FeedScore
    {
        Low = 1,
        Medium = 2,
        High = 3
    };
    FeedScore Score; // Score of the feed (Low, Medium, High)
public:
    Feed(/* args */);

    std::string Name; // Name of the feed
    Feed(const std::string& feedUrl, const std::string& name)
        : FeedUrl(feedUrl), Name(name) { } // Constructor to initialize the feed URL
    
    ~Feed() { }

    

};




