It exports to a directory structure of each subreddit's wiki, leaving behind a json (raw API response) and markdown (raw wiki page text) file for each wiki page.

The script expects a subreddits.list file in the format:

DataHoarder
Homelab
DHExchange

...separated by unix newlines \n, not Windows newlines \r\n.

There's no error handling, and you'll definitely hit the API rate limits at some point.

https://www.reddit.com/r/DataHoarder/comments/ga2p8y/is_there_a_way_to_rip_an_entire_subreddit_wiki/
