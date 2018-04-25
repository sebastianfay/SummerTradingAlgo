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

  void readInData(string ticker){
    string fileName = ticker + ".out";
    cout << fileName << endl;
    ifstream inFile(fileName);

    if (!inFile.is_open()){
      string errorMessage = "Couldn't open " + ticker + ".out";
      throw runtime_error(errorMessage);
    }
    else{ cout << "Opened " << ticker << ".out successfully!\n";}

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


public:
  vector<dataPoint> data;
};  //Niseko

int main(){
  std::ios_base::sync_with_stdio(false);  //for speed

  //main block
  try{
    Niseko snow;
    snow.readInData("I");
  }
  catch(runtime_error &error) {
    cerr << error.what() << endl;
    return 1;
  }


  return 0;
}   //main
