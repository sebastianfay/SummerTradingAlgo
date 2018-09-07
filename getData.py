# Sebastian Fay

# The purpose of this file is to retrieve the current and historical RSI,
# MACD, and price data of certain stocks and print them in a .txt file so
# that it can be easily read and analyzed by my c++ programs.

import json
import requests
import time

apiKey = "LFUM3T5DS62ZKDC0"

# get all the tickers in stockList.txt into a data structure called stockList
with open('stockList.txt', 'r') as myfile:
  stockList = myfile.read().splitlines()

# for ticker in stockList:
ticker = "SPY"

# Getting the daily price data
fp = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol="
lp = "&outputsize=full&apikey=LFUM3T5DS62ZKDC0"
requestString = fp + ticker + lp
data_time_series = requests.get(requestString).json()

dataOPEN = []
dataHIGH = []
dataLOW = []
dataCLOSE = []
dataVOLUME = []
dataDATE = []

for daily in data_time_series['Time Series (Daily)']:
    dataOPEN.append(data_time_series['Time Series (Daily)'][daily]['1. open'])
    dataHIGH.append(data_time_series['Time Series (Daily)'][daily]['2. high'])
    dataLOW.append(data_time_series['Time Series (Daily)'][daily]['3. low'])
    dataCLOSE.append(data_time_series['Time Series (Daily)'][daily]['4. close'])
    dataVOLUME.append(data_time_series['Time Series (Daily)'][daily]['5. volume'])
    dataDATE.append(daily)


fp = "https://www.alphavantage.co/query?function=EMA&symbol="
lp = "&interval=daily&time_period=9&series_type=close&apikey=LFUM3T5DS62ZKDC0"
requestString = fp + ticker + lp
data_ema = requests.get(requestString).json()

dataEMA = []

for daily in data_ema['Technical Analysis: EMA']:
    dataEMA.append(data_ema['Technical Analysis: EMA'][daily]['EMA'])

# printing all off the data into a .txt file
fileName = ticker + ".txt"
f = open(fileName, 'w')
for value in range(len(dataEMA)):
    f.write(dataDATE[value])
    f.write(" ")
    f.write(dataOPEN[value])
    f.write(" ")
    f.write(dataHIGH[value])
    f.write(" ")
    f.write(dataLOW[value])
    f.write(" ")
    f.write(dataCLOSE[value])
    f.write(" ")
    f.write(dataEMA[value])
    f.write("\n")
f.close()
