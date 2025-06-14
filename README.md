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
- [ ] Investigate FMT library options, i.e alignment and other improvements.

## Regresion to Fix
- [x] **FIXED** Somewhere along the line saving to file no longer stores ratings. Reimplement this.

## Ideas
* Show a summary of news:
1) Today's feeds only
2) Limit the number of news items shown for each Feed.

## Current Output
**Help Info**
```
$ ./rss-reader -h
Usage: rss-reader [OPTIONS]
  -l, --list                List available feeds
  -s, --show <index>        Show all news items in the selected feed
  -a, --add <name> <url>    Add a new feed
  -d, --delete <index>      Delete a feed by index
  -r, --rate <index> <rating>  Rate a feed (1=Low, 2=Medium, 3=High)
  -h, --help                Show this help message
  -v, --version             Show application version
```

**List Feeds**
```
$ ./rss-reader -l
Available Feeds:
[1] Feed Name:Techcrunch                Feed URL:https://techcrunch.com/feed/   Score: High
[2] Feed Name:Wired Top Stories         Feed URL:https://www.wired.com/feed/rss Score: Unscored
[3] Feed Name:Windows Central           Feed URL:http://feeds.windowscentral.com/wmexperts      Score: Unscored
[4] Feed Name:Bleeping Computer         Feed URL:https://www.bleepingcomputer.com/feed/ Score: Medium
[5] Feed Name:CNET News         Feed URL:https://www.cnet.com/rss/news/ Score: Unscored
```