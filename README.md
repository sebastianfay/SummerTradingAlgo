# Summer Algo Trading Project
## **Notes:**
Please do not make any trading decisions based on what you see in this repo. This project is simply a project of mine that is my exporation in my passion for CS and my deep interest in trading. 

## **Project Goals:**
My goal for this repo is to be my personal trading assistant, complete with a script to get all the necesary data, another script to evaluate and recommend trading opportunities based on what I am calling niseko, which I will get into later. Finally, I will create a script that updates a .txt file that tracks all the information about the trades that I make. This file will have my thoughts on both sides of the trade and other simple observations.

## **Trading Strategy:**
My first strategy that I will be trading is what I'm gonna name Niseko (not for any special reason I just really like Niseko, Japan). This strategy is a swing trading stratgy where I expect to be taking positions for a few days but not longer than 2 weeks. I expect that I will be trading mostly leveraged ETF's and ETN's with this strategy. 

**Entry** to trades will be after a security strats rebouding for support levels that are inline with previous support levels. I will then look for several confirmations of an uptrend using several technical indicators. Firstly, I will look for the price to rise above the 9-period EMA, mostly on a 4-hour chart. Additionally, I will look for the MACD-Histogram (12, 26, 9) to be both positive and increasing at an increasing rate. Finally, I will look for the RSI (14-period) to be increasing for over-sold (or close to) levels. I have not yet decided the threshold for certain aspects of the strategy such as acceptble RSI levels and how long above the EMA will constitute a promising trading opportunity. 
If all of these coniditons are met at the current time, I will only enter positions where the most recent support and resistance levels have a close to 10% difference. 

**Exit** from these trades has not been decided yet but will most likley be signaled by a decrease in the MACD-Histogram levels when the security is near or at the price of the most recent resistance. 

I have not decided how I will decide my **trade size**, updates to come.


## Whats in the Repo
**GetData.py:**

**niseko.cpp:**

**tradeLog.h:**

**tradeTracker.cpp**

**trades.txt:**
