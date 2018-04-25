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

fp = "https://www.alphavantage.co/query?function=RSI&symbol="
lp = "&interval=1min&time_period=14&series_type=close&apikey=LFUM3T5DS62ZKDC0"
requestString = fp + "I" + lp
data_rsi = requests.get(requestString).json()

dataRSI = []

for daily in data_rsi['Technical Analysis: RSI']:
    dataRSI.append(data_rsi['Technical Analysis: RSI'][daily]['RSI'])
