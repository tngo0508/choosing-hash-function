#include "ItemCollection.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int barcode) {
  // TO BE COMPLETED
  unsigned int d;
  d = barcode / 1000000;
  d %= 10;
  return d;
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int barcode) {
  // TO BE COMPLETED
  unsigned int d;
  d = barcode / 100000;
  d %= 10;
  return d;
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int barcode) {
  // TO BE COMPLETED
  unsigned int d;
  d = barcode / 10000;
  d %= 10;
  return d;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int barcode) {
  // TO BE COMPLETED
  unsigned int d;
  d = barcode / 1000;
  d %= 10;
  return d;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int barcode) {
  // TO BE COMPLETED
  unsigned int d;
  d = barcode / 100;
  d %= 10;
  return d;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct6(unsigned int barcode) {
  // TO BE COMPLETED
  unsigned int d;
  d = barcode / 10;
  d %= 10;
  return d;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct7(unsigned int barcode) {
  // TO BE COMPLETED
  unsigned int d;
  d = barcode % 10;
  return d;
}

// Constructor for struct Item
Item::Item(string itemColor, string itemShape, string itemBrand,
           unsigned int barcode)
    : itemColor_(itemColor),
      itemShape_(itemShape),
      itemBrand_(itemBrand),
      barcode_(barcode){};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void ItemCollection::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemColor;
    string itemShape;
    string itemBrand;
    unsigned int barcode;
    while (myfile >> itemColor >> itemShape >> itemBrand >> barcode) {
      if (itemColor.size() > 0)
        addItem(itemColor, itemShape, itemBrand, barcode);
    }
    myfile.close();
  } else
    throw std::invalid_argument("Could not open file " + filename);
}

void ItemCollection::addItem(string itemColor, string itemShape,
                             string itemBrand, unsigned int barcode) {
  // TO BE COMPLETED
  // function that adds the specified pair of glasses to main display (i.e., to
  // all hash tables)
  struct Item current_item = {itemColor, itemShape, itemBrand, barcode};

  hT1[barcode] = current_item;
  hT2[barcode] = current_item;
  hT3[barcode] = current_item;
  hT4[barcode] = current_item;
  hT5[barcode] = current_item;
  hT6[barcode] = current_item;
  hT7[barcode] = current_item;
}

bool ItemCollection::removeItem(unsigned int barcode) {
  // TO BE COMPLETED
  // function that removes the pair of glasses specified by the barcode from the
  // display if pair is found, then it is removed and the function returns true
  // else returns false
  CustomHashTable::const_iterator found;
  for (unsigned int i = 0; i < 8; ++i) {
    switch (i) {
      case 0:
        found = hT1.find(barcode);
        if (found == hT1.end()) return false;
        hT1.erase(barcode);
        break;

      case 1:
        found = hT2.find(barcode);
        if (found == hT2.end()) return false;
        hT2.erase(barcode);
        break;

      case 2:
        found = hT3.find(barcode);
        if (found == hT3.end()) return false;
        hT3.erase(barcode);
        break;

      case 3:
        found = hT4.find(barcode);
        if (found == hT4.end()) return false;
        hT4.erase(barcode);
        break;

      case 4:
        found = hT5.find(barcode);
        if (found == hT5.end()) return false;
        hT5.erase(barcode);
        break;

      case 5:
        found = hT6.find(barcode);
        if (found == hT6.end()) return false;
        hT6.erase(barcode);
        break;

      case 6:
        found = hT7.find(barcode);
        if (found == hT7.end()) return false;
        hT7.erase(barcode);
        break;

      default:
        break;
    }
  }

  return true;
}

unsigned int ItemCollection::bestHashing() {
  // TO BE COMPLETED
  // function that decides the best has function, i.e. the ones among
  // fct1-fct7 that creates the most balanced hash table for the current
  // ItemCollection data member allItems

  // Hints:
  // Calculate the balance of each hashtable, one by one.
  /*
   for (unsigned i=0; i<10; ++i) {
cout << hT1.bucket_size(i); // Call bucket_size() to get the size of each bucket
}
  */
  // Then, calculate the lowest balance

  unsigned int balance[8];
  balance[0] = 0;

  unsigned int min_loc, max_loc, min_val;

  for (unsigned int i = 1; i < 8; ++i) {
    unsigned int bucket_vals[10];
    for (unsigned int j = 0; j < 10; ++j) {
      switch (i) {
        case 1:
          bucket_vals[j] = hT1.bucket_size(j);
          break;

        case 2:
          bucket_vals[j] = hT2.bucket_size(j);
          break;

        case 3:
          bucket_vals[j] = hT3.bucket_size(j);
          break;

        case 4:
          bucket_vals[j] = hT4.bucket_size(j);
          break;

        case 5:
          bucket_vals[j] = hT5.bucket_size(j);
          break;

        case 6:
          bucket_vals[j] = hT6.bucket_size(j);
          break;

        case 7:
          bucket_vals[j] = hT7.bucket_size(j);
          break;

        default:
          break;
      }
    }

    min_loc = *std::min_element(bucket_vals, bucket_vals + 10);
    max_loc = *std::max_element(bucket_vals, bucket_vals + 10);

    balance[i] = max_loc - min_loc;
  }

  min_val = balance[1];
  for (size_t i = 2; i < 8; i++) {
    if (min_val > balance[i]) {
      min_val = balance[i];
      min_loc = i;
    }
  }

  return min_loc;
}

// ALREADY COMPLETED
size_t ItemCollection::size() {
  if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) ||
      (hT1.size() != hT4.size()) || (hT1.size() != hT5.size()) ||
      (hT1.size() != hT6.size()) || (hT1.size() != hT7.size()))
    throw std::length_error("Hash table sizes are not the same");

  return hT1.size();
}
