#pragma once

#include <vector>
#include <string>

#include "decklinkSDK/DeckLinkAPI.h"

using namespace std;

class DeckLink {
public:
  struct displayMode {
    string  name;
    int     width;
    int     height;
    int     frameRate;

    bool compare(const displayMode &other) {
      return  name.compare(other.name) &&
              width == other.width &&
              height == other.height &&
              frameRate == other.frameRate;
    }
  };
  ~DeckLink();
  DeckLink();
  DeckLink(const string &nameOfDevice);

  bool connectTo(const string &nameOfDevice);
  void close();
  bool isOpen();

  vector<displayMode> getOutputModes();
  //bool setOutMode(displayMode);

  static vector<string> getDecklinkNames();

private:
  string name;
  IDeckLink *BMDeckLink;
};
