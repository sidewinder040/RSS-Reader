#include "rss-reader.h"

RSSReader::RSSReader(const std::string& feedUrl) {
    // Constructor implementation
   std::cout << "RSSReader initialized with feed URL: " << feedUrl << std::endl;
    this->feedUrl = feedUrl;
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


        // TODO: Move the output to displayFeedItems() method
        std::cout << "Title: " << (title ? title : "No title") << std::endl;
        std::cout << "Link: " << (link ? link : "No link") << std::endl;
        std::cout << "Description: " << (description ? description : "No description") << std::endl;
        std::cout << std::endl;

        item = item->NextSiblingElement("item");
    }
    std::cout << "Feed fetched and parsed successfully." << std::endl;
    
}

void RSSReader::displayFeedItems() const {
    std::cout << "Displaying feed items..." << std::endl;
    // Here you would typically iterate over the parsed feed items and display them
    // For demonstration, we'll just print a placeholder message
    std::cout << "Feed item 1: Example Item 1" << std::endl;
    std::cout << "Feed item 2: Example Item 2" << std::endl;
    std::cout << "Feed item 3: Example Item 3" << std::endl;
    // In a real implementation, you would replace the above with actual feed item data
    // For example, you might have a vector of feed items and iterate over it:
    // for (const auto& item : feedItems) {
    //     std::cout << "Feed item: " << item.title << std::endl;
    // }
}

// Callback function to write data fetched by libcurl
size_t RSSReader::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}