// RSS Reader Application
// This application allows users to manage RSS feeds, including adding, deleting, and displaying feed items.
// It uses the TinyXML2 library for XML parsing and the cURL library for fetching RSS feeds.
// It also uses the fmt library for formatted output.
// By Mark Crouch, 2025
#pragma once
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "rss-reader.h"

void ListAvailableFeeds(const RSSReader& rssReader);