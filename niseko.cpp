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

class Niseko {
public:

  struct dataPoint {
    double price;
    double rsi;
    double macd;
    double macdSig;
    double macdHist;
  };  //dataPoint

  Niseko(string tickerName) {
    ticker = tickerName;
    data.reserve(100);
    validRsi = false;
    validMacd = false;
    priceIncreasing = false;
  }   //Niseko

  void readInData() {
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

  void findRsiCross() {
    size_t index = 0;
    if (data[index].rsi <= 30) {
      return;
    }
    while (!validRsi && index < 35) {
      if (data[index].rsi <= 30) {
        validRsi = true;
        rsiIndex = index;
      }
      ++index;
    }
  }   //findRsiCross


  void macdAnalysis() {
    macdPos = ((data[0].macdHist > 0) ? true : false);

    if (macdPos) {
      double prevHist = data[0].macdHist;
      size_t index = 1;
      while (data[index].macdHist >= 0) {
        if (data[index].macdHist >= prevHist) {
          return;
        }
        ++index;
      }
      if (index < 5 && index + 10 < rsiIndex) {
        validMacd = true;
        macdIndex = index;
        return;
      }
    }
    else {
      double prevHist = data[0].macdHist;
      size_t index = 1;
      while (data[index].macdHist < prevHist) {
        ++index;
        prevHist = data[index].macdHist;
      }
      if (index >= 4 && index + 5 > rsiIndex) {
        macdIndex = index;
        validMacd = true;
      }
    }
  }   //macdAnalysis

  void priceGoingUp() {
    priceIncreasing = data[0].price > data[rsiIndex].price;
  }   //priceGoingUp

  void runDat() {
    findRsiCross();
    if (validRsi) {macdAnalysis();}
    if (validMacd) {priceGoingUp();}

  }

void printSummary(){
  cout << "-------------------------------------------------------------\n";
  cout << endl << ticker << endl;

  if (validRsi) {
    cout << "RSI: Valid\n";
    cout << "RSI crossed above 30, " << rsiIndex << " minutes ago\n";
  } else {
    cout << "RSI: Not valid\n";
  }
  cout << endl;

  if (validMacd) {
    cout << "MACD: Valid\n";
    if (macdPos) {
      cout << "MACD HIST: Positive\n";
      cout << "MACD crossed " << macdIndex << " minutes ago\n";
    } else {
      cout << "MACD HIST: Negative\n";
      cout << "Has been increasing for " << macdIndex << " minutes\n";
    }
  } else{
    cout << "MACD: Not valid\n";
  }
  cout << endl;

  if (priceIncreasing) {
    cout << "Price has been increasing since RSI cross\n";
  } else {
    cout << "Price has NOT been increasing since RSI cross\n";
  }
  cout << endl;

  if (validRsi && validMacd && priceIncreasing) {
    cout << "BUY " << ticker << endl;
  } else {
    cout << "DO NOT BUY " << ticker << endl;
  }
  cout << endl;

  cout << "-------------------------------------------------------------\n";
}

public:
  vector<dataPoint> data;
  size_t rsiIndex;
  bool validRsi;
  size_t macdIndex;
  bool validMacd;
  bool macdPos;
  bool priceIncreasing;
  string ticker;
};  //Niseko

int main(){
  std::ios_base::sync_with_stdio(false);  //for speed

  //main try block
  ifstream inFile("stockList.txt");
  if (!inFile.is_open()){
    cout << "Couldn't open stockList.txt\n";
  }

  vector<string> tickers;

  string tempTicker;
  while (inFile >> tempTicker) {
    tickers.push_back(tempTicker);
  }

  for (size_t i = 0; i < tickers.size(); ++i) {
    try{
      Niseko snow(tickers[i]);
      snow.readInData();
      snow.runDat();
      snow.printSummary();
    }
    catch(runtime_error &error) {
      cerr << error.what() << endl;
      return 1;
    }
  }

  return 0;
}   //main
