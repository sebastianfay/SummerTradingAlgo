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
// This strategy uses short term trend trading techniques to verify a mean
// reversion trade signal

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

class Niseko{
public:

  struct dataPoint{
    double price;
    double rsi;
    double macd;
    double macdSig;
    double macdHist;
  };  //dataPoint

  Niseko(string tickerName){
    ticker = tickerName;
    data.reserve(100);
  }   //Niseko

  void readInData(){
    string fileName = ticker + ".out";
    //cout << fileName << endl;
    ifstream inFile(fileName);

    if (!inFile.is_open()){
      string errorMessage = "Couldn't open " + ticker + ".out";
      throw runtime_error(errorMessage);
    }

    string temp;
    double rsi;
    double price;
    double macd;
    double macdHist;
    double macdSig;
    while (inFile >> temp >> temp >> price >> rsi >> macd >> macdSig >> macdHist) {
      dataPoint temp;
      temp.price = price;
      temp.rsi = rsi;
      temp.macd = macd;
      temp.macdSig = macdSig;
      temp.macdHist = macdHist;
      data.push_back(temp);
    }
  }   //readInData

  bool verifyPreMACD(){
    for (size_t i = macdIndex; i < macdIndex + 40; i++) {
      if (data[i].macdHist > 0) {
        return false;
      }
    }
    return true;
  }   //verifyPreMACD

  bool verifyPriceIncrease(){
    if (data[macdIndex].price >= data[rsiIndex].price) {
      return true;
    }
    return false;
  }   //verifyPriceIncrease

  bool findCrosses(){
    bool foundRsi = false;
    bool foundMacd = false;
    for (size_t i = 0; i < data.size(); ++i) {
      if (data[i].macdHist <= 0 && !foundMacd) {
        macdIndex = i;
        foundMacd = true;
        // cout << macdIndex << endl;
      }
      if (data[i].rsi <= 30.0 && !foundRsi) {
        rsiIndex = i;
        foundRsi = true;
        // cout << rsiIndex << endl;
      }
    }
    if (foundRsi && foundMacd) {
      if (macdIndex < rsiIndex) {
        return true;
      }
    }
    return false;
  }

  void runnit(){
    if (findCrosses()) {
      if (rsiIndex - macdIndex <= 30) {
        if (verifyPreMACD()) {
          if (verifyPriceIncrease()) {
            printBuy();
          }
          else{
          cout << "The price of " << ticker << " has not gone up between the RSI"
           << " cross over 30 and the bullish MACD crossover. It looks like"
           << " there is not a trend forming.\nDont buy it.\n";
          }
        }
        else{
          cout << "The MACD Histogram for " << ticker << " has not been negative for enough time.\n";
        }
      }
      else{
        cout << "It has been to long between the RSI crossover and the MACD"
        << " crossover. This might indicate against a trend forming.\n";
      }
    }
  }   //runnit

void printBuy(){
  cout << "Buy " << ticker << " right now\n";
}

public:
  vector<dataPoint> data;
  size_t rsiIndex;
  size_t macdIndex;
  string ticker;
};  //Niseko

int main(){
  std::ios_base::sync_with_stdio(false);  //for speed

  //main try block
  try{
    Niseko snow("I");
    snow.readInData();
    snow.runnit();
  }
  catch(runtime_error &error) {
    cerr << error.what() << endl;
    return 1;
  }

  return 0;
}   //main
