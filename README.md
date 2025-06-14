# RSS-Reader

This RSS Reader is based on a suggested implementation of a basic RSS reader suggested by Co-pilot. I've separated the fuctionality away from the main.cpp file and created the following:

* rss-reader.cpp - Acts as an loose 'interface' between Feed Models and Main calling the feed.cpp/h and feed-item.cpp/h objects. 
* feed.cpp - (Model) Is an object for a Feed, containing feed item parameters i.e. URL, user-friendly name, and scoring preference.
* feet-item.cpp - (Model) This represents an object containing Feed news attributes, i.e. Title, Summary, Link etc.
* main.cpp - Calls rss-reader only (not Model objects), setting out the view output/formatting.

## Current Features
* Loads and saves current feeds, an example file is included with tested RSS Feeds.
* User selects a Feed from the list of available feeds, to display its news items.

## To Do Items

- [x] Feed Object for multiple feed sources capability.
- [x] Command-line argument parsing for Selecting, Adding, Removing and Rating feeds.
- [x] Vector of feeds. 
- [x] Store feeds in a file and retrieve them on startup.
- [x] Maybe add fmt library for better feed formating (especially links).

## Regresion to Fix
- [x] **FIXED** Somewhere along the line saving to file no longer stores ratings. Reimplement this.

## Ideas

Summary of headlines with item ID
Display description of item ID, then usse the ID No. to display further details.
Add a limit feature, by number of items or frome the last n days.
