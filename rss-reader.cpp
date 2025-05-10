#include "rss-reader.h"

RSSReader::RSSReader(const std::string& feedUrl) {

    // TODO: Initialize feeds with a Vector of feed objects

    // Constructor implementation
   std::cout << "RSSReader initialized with feed URL: " << feedUrl << std::endl;

    // Initialize the feed URL
    this->feedUrl = feedUrl;
}

void RSSReader::AddFeed(const Feed& feed) {
    feeds.push_back(feed);
}
void RSSReader::RemoveFeed(const std::string& feedUrl) {
    // Find the feed with the given URL and remove it from the vector
    auto it = std::remove_if(feeds.begin(), feeds.end(), [&feedUrl](const Feed& feed) {
        return feed.FeedName == feedUrl;
    });
    if (it != feeds.end()) {
        feeds.erase(it, feeds.end());
        std::cout << "Feed removed: " << feedUrl << std::endl;
    } else {
        std::cout << "Feed not found: " << feedUrl << std::endl;
    }
}

void RSSReader::FetchFeed()
{
    // Initialize CURL
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, feedUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            // return 1;
        }
    }

    tinyxml2::XMLDocument doc;
    if (doc.Parse(readBuffer.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to parse XML" << std::endl;
        // return 1;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("rss");
    if (!root) {
        std::cerr << "No RSS element found" << std::endl;
        // return 1;
    }

    tinyxml2::XMLElement* channel = root->FirstChildElement("channel");
    if (!channel) {
        std::cerr << "No channel element found" << std::endl;
        // return 1;
    }

    tinyxml2::XMLElement* item = channel->FirstChildElement("item");

    // TODO: Parse the feed items and store them in the feedItems vector
    while (item) {
        const char* title = item->FirstChildElement("title")->GetText();
        const char* link = item->FirstChildElement("link")->GetText();
        const char* description = item->FirstChildElement("description")->GetText();

        // Create a feed_item object and add it to the feedItems vector
        feed_item newItem(title ? title : "", link ? link : "", description ? description : "");
        feedItems.push_back(newItem); // Store the title in the vector        
        
        item = item->NextSiblingElement("item");
    }
    std::cout << "Feed fetched and parsed successfully." << std::endl;   
}

void RSSReader::displayFeedItems() const {
    std::cout << "Displaying feed items..." << std::endl;
    // Iterate over the feed items and display them
    for (const auto& item : feedItems) {

        std::cout << "Title: " << item.title << std::endl;
        std::cout << "Description: " << item.description << std::endl;
        std::cout << "Link: " << item.link << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
}

// Callback function to write data fetched by libcurl
size_t RSSReader::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}