#pragma once
#include <string>

class feed_item
{
// private:
    /* data */
public:
    feed_item(/* args */);
    feed_item(const std::string& title, const std::string pubdate,const std::string& link, const std::string& description)
        : title(title), pubDate(pubdate) ,link(link), description(description) { }
    ~feed_item() { }
    std::string title;
    std::string pubDate;
    std::string link;
    std::string description;
    // std::string pubDate;
};


