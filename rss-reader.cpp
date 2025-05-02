#include "rss-reader.h"

RSSReader::RSSReader(const std::string& feedUrl) {
    // Constructor implementation
   std::cout << "RSSReader initialized with feed URL: " << feedUrl << std::endl;
}

void RSSReader::FetchFeed()
{
    // Initialize CURL
    curl = curl_easy_init();
    if (curl) {
        // Set the URL of the RSS feed
        curl_easy_setopt(curl, CURLOPT_URL, feedUrl.c_str());
        // Set the write function to handle the response data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        // Perform the request
        res = curl_easy_perform(curl);
        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        // Cleanup
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize CURL" << std::endl;
    }
    // Parse the XML response
    if (doc.LoadFile("response.xml") != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load XML file" << std::endl;
        return;
    }
    // Here you would typically parse the XML document and extract feed items
    // For demonstration, we'll just print a placeholder message
    std::cout << "Parsing XML response..." << std::endl;
    // In a real implementation, you would replace the above with actual parsing logic
    // For example, you might use tinyxml2 to iterate over the XML elements and extract data:
    // tinyxml2::XMLElement* item = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");


    // while (item) {
    //     const char* title = item->FirstChildElement("title")->GetText();
    //     if (title) {
    //         feedItems.push_back(title);
    //     }
    //     item = item->NextSiblingElement("item");
    // }
    // For demonstration, we'll just add some dummy feed items
    feedItems.push_back("Example Item 1");
    feedItems.push_back("Example Item 2");
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