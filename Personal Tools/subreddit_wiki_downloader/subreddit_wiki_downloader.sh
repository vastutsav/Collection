#! /bin/bash

# Requires: bash coreutils curl jq

USER_AGENT='superagent/1.0'
EXPORTDIR="exports"

while read -r line; do
	SUBREDDIT="$line"

	while read -r line; do
	PAGE="$line" ; PAGE=$(echo $PAGE | sed 's|\/|\-\-|g')

	mkdir -p "./$EXPORTDIR/$SUBREDDIT/wiki/$PAGE"
	curl -s --user-agent "$USER_AGENT" "https://www.reddit.com/r/$SUBREDDIT/wiki/$PAGE.json" > "./$EXPORTDIR/$SUBREDDIT/wiki/$PAGE.json"
	printf "$SUBREDDIT/wiki/$PAGE   " ; echo $?
	jq -r '.data.content_md' "./$EXPORTDIR/$SUBREDDIT/wiki/$PAGE.json" > "./$EXPORTDIR/$SUBREDDIT/wiki/$PAGE.md"
	find . -type d -exec rmdir '{}' \; > /dev/null 2>&1

	done < <(curl -S --user-agent "$USER_AGENT" "https://www.reddit.com/r/$SUBREDDIT/wiki/pages.json" | jq -r '.data | .[]')

done < subreddits.list
