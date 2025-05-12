# RSS-Reader

This RSS Reader is by expanding a suggestion for a basic RSS reader suggested by Co-pilot. I've separated the fuctionality away from the main.cpp file and created the following:

* rss-reader.cpp - Acts like a Controller, calling the feed.cpp/h and feed-item.cpp/h objects
* feed.cpp - (Model) Is an object for a feet, containing feed item parameters i.e. URL, user-friendly name, and scoring preference.
* feet-item.cpp - (Model) This is used as an object to contain Feed, news items.
* main.cpp - (View) Calls rss-reader (Controller) only (not Model objects), setting out the view output/formatting.

## To Do Items

1) Feed Object for multiple feed sources capability.
2) Vector of feeds. Config file to store feeds.
3) Store feeds to a file.
4) Maybe add fmt library for better feed formating (especially links).

## Ideas

Summary of headlines with item ID
Display description of item ID, then usse the ID No. to display further details.
Scoring of Feeds to prioritise favourite sources
Add a limit feature, by number of items or frome the last n days.
