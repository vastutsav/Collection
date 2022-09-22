import pandas as pd
import numpy as np
import yfinance as yf
import datetime as dt
from pandas_datareader import data as pdr

yf.pdr_override()

stock=input("Enter a stock ticker symbol: ")
print(stock)

startyear=2010
startmonth=1
startday=1

start=dt.datetime(startyear,startmonth,startday)

now=dt.datetime.now()

df=pdr.get_data_yahoo(stock,start,now)

# ma=50

# smaString="Sma_"+str(ma)

# df[smaString]=df.iloc[:,4].rolling(window=ma).mean()


smasUsed=[20,200]
for x in smasUsed:
	df["Sma_"+str(x)]=round(df.iloc[:,4].rolling(window=x).mean())


df=df.iloc[60:]

pos=0
num=0
percentchange=[]

for i in df.index:
	cmin=df["Sma_20"][i]
	cmax=df["Sma_200"][i]

	close=df["Adj Close"][i]
	
	if cmin>cmax and close > cmin:
		# print("Red White Blue")
		if(pos==0):
			bp=close
			pos=1
			print("Buying now at "+str(bp))


	else:
		# print("Blue White Red")
		if(pos==1):
			pos=0
			sp=close
			print("Selling now at "+str(sp))
			pc=(sp/bp-1)*100
			percentchange.append(pc)
	if(num==df["Adj Close"].count()-1 and pos==1):
		pos=0
		sp=close
		print("Selling now at "+str(sp))
		pc=(sp/bp-1)*100
		percentchange.append(pc)

	num+=1

print(percentchange)

gains=0
ng=0
losses=0
nl=0
totalR=1

for i in percentchange:
	if(i>0):
		gains+=i
		ng+=1
	else:
		losses+=i
		nl+=1
	totalR=totalR*((i/100)+1)

totalR=round((totalR-1)*100,2)

if(ng>0):
	avgGain=gains/ng
	maxR=str(max(percentchange))
else:
	avgGain=0
	maxR="undefined"

if(nl>0):
	avgLoss=losses/nl
	maxL=str(min(percentchange))
	ratio=str(-avgGain/avgLoss)
else:
	avgLoss=0
	maxL="undefined"
	ratio="inf"

if(ng>0 or nl>0):
	battingAvg=ng/(ng+nl)
else:
	battingAvg=0

print()
print("Results for "+ stock +" going back to "+str(df.index[0])+", Sample size: "+str(ng+nl)+" trades")
print("SMAs used: "+str(smasUsed))
print("Win%: "+ str(round(battingAvg*100, 2)) + "%")
print("Gain/loss ratio: "+ ratio)
print("Average Gain: "+ str(avgGain))
print("Average Loss: "+ str(avgLoss))
print("Max Return: "+ maxR)
print("Max Loss: "+ maxL)
print("Total return over "+str(ng+nl)+ " trades: "+ str(totalR)+"%" )
#print("Example return Simulating "+str(n)+ " trades: "+ema str(nReturn)+"%" )
print()