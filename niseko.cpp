#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

class Niseko {
public:

  struct candle {
    double open;
    double high;
    double low;
    double close;
  };

  struct dataPoint {
    candle body;
    string date;
    double ema;
  };

  Niseko(string ticker) {
    ticker = ticker;
    percentage = 1.000;
  }

  void loadData() {
    ifstream infile;
    infile.open("SPY.txt");

    string date;
    double open;
    double high;
    double low;
    double close;
    double ema;

    string line;

    while (infile >> date >> open >> high >> low >> close >> ema) {
      candle temp;
      temp.open = open;
      temp.high = high;
      temp.low = low;
      temp.close = close;

      dataPoint tempData;
      tempData.body = temp;
      tempData.date = date;
      tempData.ema = ema;

      data.push_back(tempData);
    }
    cout << "Data loaded" << endl;
  }

  bool isCrossingCandleBull(size_t index) {
    if (data[index].ema > data[index].body.low) {
      if (min(data[index].body.close, data[index].body.open) > data[index].ema) {
        return true;
      }
    }
    return false;
  }

  bool isCrossingCandleBear(size_t index) {
    if (data[index].ema < data[index].body.high) {
      if (max(data[index].body.close, data[index].body.open)  < data[index].ema) {
        return true;
      }
    }
    return false;
  }

  bool emaCorrectTrendBull(size_t index) {
    if (data[index].ema > data[index+1].ema && data[index+1].ema > data[index+2].ema) {
      return true;
    }
    return false;
  }

  bool emaCorrectTrendBear(size_t index) {
    if (data[index].ema < data[index+1].ema && data[index+1].ema < data[index+2].ema) {
      return true;
    }
    return false;
  }

  void isACurrentBuy() {
    if ((emaCorrectTrendBull(0) && isCrossingCandleBull(0)) || (emaCorrectTrendBear(0) && isCrossingCandleBear(0))) {
      cout << "SPY is a current buy, sell it right before close tomorrow" << endl;
    }
    else{
      cout << "SPY is NOT a current buy" << endl;
    }
  }

  void backTest() {
    for (size_t i = data.size()-4; i > 0; i--) {
      if (emaCorrectTrendBull(i) && isCrossingCandleBull(i)) {
        cout << data[i].date <<  " " << getNextDayIncreaseBull(i) << " " << this->percentage << endl;
      }
      if (emaCorrectTrendBear(i) && isCrossingCandleBear(i)) {
        cout << data[i].date <<  " " << getNextDayIncreaseBear(i) << " " << this->percentage << endl;
      }
    }
  }

  double getNextDayIncreaseBull(size_t index) {
    double nextDayPercentage = (data[index-1].body.close - data[index].body.close) / data[index].body.close + 1.00;
    updateBackTestPercentage(nextDayPercentage);
    return nextDayPercentage;
  }

  double getNextDayIncreaseBear(size_t index) {
    double nextDayPercentage = (data[index].body.close - data[index-1].body.close) / data[index].body.close + 1.00;
    updateBackTestPercentage(nextDayPercentage);
    return nextDayPercentage;
  }

  void updateBackTestPercentage(double percentage) {
    this->percentage *= percentage;
  }

public:
  vector<dataPoint> data;
  string ticker;
  double percentage;
};

int main() {
  Niseko runner("SPY");
  runner.loadData();

  string response;
  cin >> response;
  if (response == "B") {
    runner.backTest();
  }
  else {
    runner.isACurrentBuy();
  }
}
