// Sebastian Fay

// This file will be a .txt file that keeps track of all my trades

// They will have the basic trade stats as well as my personal reason for trading
// this particular ticker at this particular time

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>  //for the datetime

class TradeLogInput {
public:
  time_t buyDate;
  string ticker;
  double price;
  string reason;
};    //TradeLogInput
