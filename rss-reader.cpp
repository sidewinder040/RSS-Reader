#include "rss-reader.h"


// Constructor implementation
// Default constructor
RSSReader::RSSReader() { }    

RSSReader::RSSReader(const std::string& feedName, const std::string& feedUrl) {
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
void RSSReader::RemoveFeed(const std::string& feedName) {
    // Find the feed with the given URL and remove it from the vector
    auto it = std::remove_if(feeds.begin(), feeds.end(), [&feedName](const Feed& feed) {
        return feed.FeedName == feedName;
    });
    if (it != feeds.end()) {
        feeds.erase(it, feeds.end());
        std::cout << "Feed removed: " << feedName<< std::endl;
    } else {
        std::cout << "Feed not found: " << feedName << std::endl;
    }
}

void RSSReader::RemoveFeedByIndex(int index) {
    if (index < 0 || index >= (int)feeds.size()) {
        std::cout << "Invalid feed index." << std::endl;
        return;
    }
    std::string feedName = feeds[index].FeedName;
    feeds.erase(feeds.begin() + index);
    std::cout << "Feed removed: " << feedName << std::endl;
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
    
    // Initialize libcurl
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
    // Check if the readBuffer is empty
    if (readBuffer.empty()) {
        std::cout << "No data fetched from the selected feed URL." << std::endl;
        return;
    }   
    // Parse the XML data using tinyxml2
    tinyxml2::XMLDocument doc;
    if (doc.Parse(readBuffer.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cout << "Failed to parse XML" << std::endl;
        return;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("rss");
    if (!root) {
        std::cout << "No RSS element found" << std::endl;
        return;
    }

    tinyxml2::XMLElement* channel = root->FirstChildElement("channel");
    if (!channel) {
        std::cout << "No channel element found" << std::endl;
        return;
    }

    tinyxml2::XMLElement* item = channel->FirstChildElement("item");

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
    // Check if there are any feed items to display
    if (feedItems.empty()) {
        std::cout << "No feed items available to display." << std::endl;
        return;
    }
    // Display the feed items
    std::cout << "Displaying feed items..." << std::endl;
    for (const auto& item : feedItems) {
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
        std::cout << "------------------------"
            << "------------------------" 
            << std::endl;
    }
}

void RSSReader::SaveFeedsToFile(const std::string& filename, const std::vector<Feed> &feeds) {
    // Open the file in write mode
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    
    // Write the feeds to the file
    for (const auto& feed : feeds) {
        outFile << feed.FeedName << "," << feed.GetFeedUrl() << "," << static_cast<int>(feed.FeedScore) << std::endl;
        // std::cout << "Feed saved: " << feed.FeedName << " (" << feed.GetFeedUrl() << ")" << std::endl;
    }
    outFile.close();
}

void RSSReader::LoadFeedsFromFile(const std::string& filename) {
    // Open the file in read mode
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }
    
    // Read the feeds from the file
    std::string line;
    while (std::getline(inFile, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            std::string feedName = line.substr(0, commaPos);
            std::string feedUrl = line.substr(commaPos + 1);
            // load the feed score after the feed URl
            
            size_t secondCommaPos = feedUrl.find(',', commaPos + 1);
            Feed::EnumScore feedScore = Feed::UNSCORED; // Default score
            if (secondCommaPos != std::string::npos) {
                feedScore = static_cast<Feed::EnumScore>(std::stoi(feedUrl.substr(secondCommaPos + 1)));
                feedUrl = feedUrl.substr(0, secondCommaPos); // Extract the URL part
            }
            // Create a Feed object and add it to the feeds vector
            // std::cout << "Feed loaded: " << feedName << " (" << feedUrl << ")" << std::endl;

            feeds.push_back(Feed(feedUrl, feedName, feedScore));
        }
    }
    inFile.close();
}

// Callback function to write data fetched by libcurl
size_t RSSReader::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}