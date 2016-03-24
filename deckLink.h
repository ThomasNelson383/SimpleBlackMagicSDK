#include <vector>
#include <string>
#include <map>

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
      return  name.compare(other) &&
              width == other.width &&
              height == other.height &&
              frameRate == other.frameRate;
    }
  }
  ~DeckLink();
  DeckLink();
  DeckLink(const string &nameOfDevice);

  bool connectTo(const string &nameOfDevice);
  void close();
  bool isOpen();

  vector<displayMode> getOutputModes();
  setOutMode(displayMode);

  static vector<string> getDecklinkNames();

private:
  string name;
  IDeckLink *deckLink;
}
