# RSS-Reader

This RSS Reader is by expanding a suggestion for a basic RSS reader suggested by Co-pilot. I've separated the fuctionality away from the main.cpp file and created the following:

* rss-reader.cpp - Interfaces between Feed Models and Main calling the feed.cpp/h and feed-item.cpp/h objects
* feed.cpp - (Model) Is an object for a feet, containing feed item parameters i.e. URL, user-friendly name, and scoring preference.
* feet-item.cpp - (Model) This is used as an object to contain Feed, news items.
* main.cpp - Calls rss-reader only (not Model objects), setting out the view output/formatting.

## Current Features
* Loads and saves current feeds, an example file is included with tested RSS Feeds.
* User selects a Feed from the list of available feeds, to display its news items.

## To Do Items

- [x] Feed Object for multiple feed sources capability.
- [ ] A menu for Selecting, Adding, Removing and Rating feeds.
- [x] Vector of feeds. 
- [x] Store feeds in a file and retrieve them on startup.
- [x] Maybe add fmt library for better feed formating (especially links).

## Ideas

Summary of headlines with item ID
Display description of item ID, then usse the ID No. to display further details.
Scoring of Feeds to prioritise favourite sources
Add a limit feature, by number of items or frome the last n days.
