import pandas as pd
import numpy as np
import yfinance as yf
import datetime as dt
from pandas_datareader import data as pdr

yf.pdr_override()

stock = input("Enter a stock ticker symbol: ")
print(stock)

startyear = 2019
startmonth = 1
startday = 1

start=dt.datetime(startyear, startmonth, startday)
end 