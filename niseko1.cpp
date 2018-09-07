

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Niseko{
public:

  struct dataPoint {
    double price;
    double open;
    double high;
    double low;
    double close;
    double volume;
    double rsi;
    double macd;
    double macdSig;
    double macdHist;
    double ema;
  };  //dataPoint

  Niseko(string ticker) {
    this.ticker = ticker;
  }

public:
  string ticker;
  vector<dataPoint> data;
};
