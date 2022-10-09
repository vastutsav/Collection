import pandas as pd
import numpy as np
import yfinance as yf
import datetime as dt
from pandas_datareader import data as pdr

yf.pdr_override()

stock = input("Enter a stock ticker symbol: ")
print(stock)

startyear = 2020
startmonth = 1
startday = 1

start = dt.datetime(startyear, startmonth, startday)
now = dt.datetime.now()

# get data from Yahoo finance
df = pdr.get_data_yahoo(stock, start, now)

# print(df)

# moving average
ma = 200
smaString = "Sma_" + str(ma)

df[smaString] = df.iloc[:,4].rolling(window=ma).mean()

df = df.iloc[ma:]

print(df)

numH=0
numL=0


for i in df.index:
    # i has dates
    if df["Adj Close"][i] < df[smaString][i]:
        numL+=1
    else:
        numH+=1

# print ("number of times the price was lower than the moving average is " + str(numL))
# print ("number of times the price was higher than the moving average is " + str(numH))