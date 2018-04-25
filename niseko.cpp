// Sebastian Fay

// -----------------------------------------------------------------------------
// THIS IS JUST FOR EDUCATIONAL PURPOSES, DO NOT MAKE TRADING DECISIONS BASED ON
// THIS ALGORITHM
// -----------------------------------------------------------------------------

// This program ideally will find day-trading opportunities of penny stocks
// using the RSI movement, MACD crossovers, and the price movement

// Trading Theory:
// I noticed when looking at the MACD and RSI charts of small-cap stocks that a
// possible indicator for a rise in market price are often shortly after a bullish
// MACD crossover and the RSI rising above 30 from an oversold state.

// This strategy uses mean reversion techniques to verify a forming short term
// trend, or vis versa.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Niseko{
public:

  struct dataPoint{
    double rsi;
    double price;
    double macd;
    double macdHist;
    double macdSig;
  };  //dataPoint



public:
  vector<dataPoint> data;
};  //Niseko

int main(){
  return 0;
}   //main
