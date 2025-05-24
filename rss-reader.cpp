#include "rss-reader.h"

// Constructor implementation
// Default constructor
RSSReader::RSSReader() {
    // Initialize the feed URLs
    // Some example feeds
    // Feed feed1("Techcrunch", "https://techcrunch.com/feed");
    // Feed feed2("BBC", "http://feeds.bbci.co.uk/news/rss.xml");
    // Feed feed3("CNN", "http://rss.cnn.com/rss/edition.rss");
    // feeds.push_back(feed1);
    // feeds.push_back(feed2);
    // feeds.push_back(feed3);
}    

RSSReader::RSSReader(const std::string& feedName, const std::string& feedUrl) {
    // TODO: Initialize feeds with a Vector of feed objects
    // Add given feed URL to the feeds vector
    AddFeed(Feed(feedName, feedUrl));

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

void RSSReader::FetchFeed(int feedIndex) 
{
    // Check if the feed index is valid
    if (feedIndex < 0 || feedIndex >= (int)feeds.size()) {
        std::cout << "Invalid feed index. Using default feed URL." << std::endl;
        feedIndex = 0; // Default to the first feed if index is invalid
    }
    
    // Get the feed URL from the feeds vector
    feedUrl = feeds[feedIndex].GetFeedUrl();
        
    // Fetch and parse the RSS feed
    std::cout << "Fetching RSS feed from: " << feedUrl << std::endl;

    // Initialize CURL
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    // feedUrl = feedUrl.empty() ? "https://techcrunch.com/feed/" : feedUrl; // Default to TechCrunch if no URL is provided
    
    std::string feedUrl1 = "https://www.thurrott.com/blog/rss"; // Example feed URL, can be replaced with dynamic input
    strcmp(feedUrl.c_str(), feedUrl1.c_str()) == 0 ? std::cout << "Sting URLs match " << std::endl 
        : std::cout << "URLs are different " << std::endl;
    std::cout << "Feed URL literal:\t|" << feedUrl1 << "|" << std::endl;
    std::cout << "Feed URL from Value:\t|" << feedUrl << "|" << std::endl;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, feedUrl.c_str()); // Set the feed URL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            // return 1;
        }
    }

    // std::cout << readBuffer << std::endl; // Print the fetched feed content

    tinyxml2::XMLDocument doc;
    if (doc.Parse(readBuffer.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cout << "Failed to parse XML" << std::endl;
        // return 1;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("rss");
    if (!root) {
        std::cout << "No RSS element found" << std::endl;
        // return 1;
    }

    tinyxml2::XMLElement* channel = root->FirstChildElement("channel");
    if (!channel) {
        std::cout << "No channel element found" << std::endl;
        // return 1;
    }

    tinyxml2::XMLElement* item = channel->FirstChildElement("item");

    // TODO: Parse the feed items and store them in the feedItems vector
    while (item) {
        const char* title = item->FirstChildElement("title")->GetText();
        const char* pubDate = item->FirstChildElement("pubDate")->GetText();
        const char* link = item->FirstChildElement("link")->GetText();
        const char* description = item->FirstChildElement("description")->GetText();

        // Create a feed_item object and add it to the feedItems vector
        feed_item newItem(title ? title : "", pubDate ? pubDate : "" ,link ? link : "", description ? description : "");
        feedItems.push_back(newItem); // Store the title in the vector        
        
        item = item->NextSiblingElement("item");
        // TODO: Add special character handling for title, link, and description e.g ampersand, apostrophe, etc.

    }
    std::cout << "Feed fetched and parsed successfully." << std::endl;   
}

void RSSReader::displayFeedItems() const {
    std::cout << "Displaying feed items..." << std::endl;
    // Iterate over the feed items and display them
    for (const auto& item : feedItems) {
        // Display the feed item details
        // Title
        fmt::print(fmt::emphasis::bold, "Title: ");
        fmt::print(fmt::emphasis::underline | fmt::emphasis::bold, "{}{}{}\n", RED, item.title, RESET);

        // Publication Date
        fmt::print(fmt::emphasis::bold, "Publication Date: ");
        fmt::print("{}\n", item.pubDate);

        // Description
        fmt::print(fmt::emphasis::bold, "Description: ");
        fmt::print("{}\n", item.description);
                
        // Link
        fmt::print(fmt::emphasis::bold, "Link: ");
        fmt::print(fmt::emphasis::underline, "{}{}{}\n", BLUE, item.link, RESET);
        std::cout << "----------------------------------------" << std::endl;
    }
}

// Callback function to write data fetched by libcurl
size_t RSSReader::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}