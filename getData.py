# Sebastian Fay

# The purpose of this file is to retrieve the current and historical RSI,
# MACD, and price data of certain stocks and print them in a .txt file so
# that it can be easily read and analyzed by my c++ programs.

import json
import requests

apiKey = "LFUM3T5DS62ZKDC0"

# get all the tickers in stockList.txt into a data structure called stockList
with open('stockList.txt', 'r') as myfile:
  stockList = myfile.read().splitlines()

ticker = "I"

# for ticker in stockList:
# Getting the RSI data
fp = "https://www.alphavantage.co/query?function=RSI&symbol="
lp = "&interval=1min&time_period=14&series_type=close&apikey=LFUM3T5DS62ZKDC0"
requestString = fp + ticker + lp
data_rsi = requests.get(requestString).json()

dataRSI = []

for daily in data_rsi['Technical Analysis: RSI']:
    dataRSI.append(data_rsi['Technical Analysis: RSI'][daily]['RSI'])

# Getting the MACD data
fp = "https://www.alphavantage.co/query?function=MACD&symbol="
lp = "&interval=1min&series_type=close&fastperiod=9&apikey=LFUM3T5DS62ZKDC0"
requestString = fp + ticker + lp
data_macd = requests.get(requestString).json()

dataMACD = []
dataMACDSig = []
dataMACDHist = []

for daily in data_macd['Technical Analysis: MACD']:
    dataMACD.append(data_macd['Technical Analysis: MACD'][daily]['MACD'])
    dataMACDSig.append(data_macd['Technical Analysis: MACD'][daily]['MACD_Signal'])
    dataMACDHist.append(data_macd['Technical Analysis: MACD'][daily]['MACD_Hist'])

# Getting the instraDay price data
fp = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol="
lp = "&interval=1min&apikey=LFUM3T5DS62ZKDC0"
requestString = fp + ticker + lp
data_price = requests.get(requestString).json()

dataPRICE = []
dataDATE = []

for daily in data_price['Time Series (1min)']:
    dataPRICE.append(data_price['Time Series (1min)'][daily]['4. close'])
    dataDATE.append(daily)

# printing all off the data into a .txt file
fileName = ticker + ".out"
f = open(fileName, 'w')
for value in range(len(dataPRICE)):
    f.write(dataDATE[value])
    f.write(" ")
    f.write(dataPRICE[value])
    f.write(" ")
    f.write(dataRSI[value])
    f.write(" ")
    f.write(dataMACD[value])
    f.write(" ")
    f.write(dataMACDSig[value])
    f.write(" ")
    f.write(dataMACDHist[value])
    f.write("\n")
f.close()
