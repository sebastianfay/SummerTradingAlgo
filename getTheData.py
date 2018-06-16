import json
import requests
import time

apiKey = "LFUM3T5DS62ZKDC0"

with open('stockList.txt', 'r') as myfile:
  stockList = myfile.read().splitlines()

# this is just for development so it doesn't make a million calls
# tempTickers = []
# tempTickers.append("DRIP")

# for ticker in stockList:
for ticker in stockList:
    # Getting the instraDay price data
    fp = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol="
    lp = "&interval=60min&outputsize=full&apikey=" + apiKey
    requestString = fp + ticker + lp
    data_price = requests.get(requestString).json()

    keyList = list(data_price.keys())

    if keyList[0] == 'Error Message' or keyList[0] == 'Information':
        print("couldn't get the ticker information")
        continue

    dataPriceOpen = []
    dataPriceHigh = []
    dataPriceLow = []
    dataPriceClose = []
    dataPriceVol = []

    for daily in data_price['Time Series (60min)']:
        dataPriceOpen.append(data_price['Time Series (60min)'][daily]['1. open'])
        dataPriceHigh.append(data_price['Time Series (60min)'][daily]['2. high'])
        dataPriceLow.append(data_price['Time Series (60min)'][daily]['3. low'])
        dataPriceClose.append(data_price['Time Series (60min)'][daily]['4. close'])
        dataPriceVol.append(data_price['Time Series (60min)'][daily]['5. volume'])

    fp = "https://www.alphavantage.co/query?function=RSI&symbol="
    lp = "&interval=60min&time_period=14&series_type=close&apikey=" + apiKey
    requestString = fp + ticker + lp
    data_rsi = requests.get(requestString).json()

    keyList = list(data_rsi.keys())

    if keyList[0] == 'Error Message' or keyList[0] == 'Information':
        print("couldn't get the ticker information")
        continue

    dataRSI = []

    for daily in data_rsi['Technical Analysis: RSI']:
        dataRSI.append(data_rsi['Technical Analysis: RSI'][daily]['RSI'])

    # getting the MACD data
    fp = "https://www.alphavantage.co/query?function=MACD&symbol="
    lp = "&interval=60min&series_type=close&fastperiod=9&apikey=" + apiKey
    requestString = fp + ticker + lp
    data_macd = requests.get(requestString).json()

    if keyList[0] == 'Error Message' or keyList[0] == 'Information':
        print("couldn't get the ticker information")
        continue

    dataMACD = []
    dataMACDSig = []
    dataMACDHist = []

    for daily in data_macd['Technical Analysis: MACD']:
        dataMACD.append(data_macd['Technical Analysis: MACD'][daily]['MACD'])
        dataMACDSig.append(data_macd['Technical Analysis: MACD'][daily]['MACD_Signal'])
        dataMACDHist.append(data_macd['Technical Analysis: MACD'][daily]['MACD_Hist'])

    # writing the information to a file
    fileName = ticker + ".out"
    f = open(fileName, 'w')
    for value in range(len(dataMACD)):
        f.write(dataPriceOpen[value])
        f.write(" ")
        f.write(dataPriceHigh[value])
        f.write(" ")
        f.write(dataPriceLow[value])
        f.write(" ")
        f.write(dataPriceClose[value])
        f.write(" ")
        f.write(dataPriceVol[value])
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
