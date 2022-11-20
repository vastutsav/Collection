#!/usr/bin/bash

year=$(date +%Y)
case $(date +%m) in
    01|02|03) start_date=${year}-01-01; quarter="Jan Feb Mar"; ;;
    04|05|06) start_date=${year}-04-01; quarter="Apr May Jun"; ;;
    07|08|09) start_date=${year}-07-01; quarter="Jul Aug Sep"; ;;
    10|11|12) start_date=${year}-10-01; quarter="Oct Nov Dec"; ;;
esac

date_diff=$(( ($(date +%s) - $(date -d $start_date +%s)) / (60*60*24) + 1 ))
echo "Today is <$date_diff> of the current quarter of <$quarter>"

