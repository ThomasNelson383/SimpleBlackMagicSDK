#include "deckLink.h"

void main() {
  deckLink deckLink;

  vector<string> names = deckLink.getDecklinkNames();
  //Making sure there devices to see
  if(names.size() == 0) {
    return;
  }
  //Displaying all the names of the Decklinks
  for(int i = 0; i < names.size(); ++i) {
    printf("Device %d: %s", i, names[i]);
  }
  //Connecting to the first one
  deckLink.connectTo(names[0]);
  //Displaying all the modes
  vector<displayMode> displayModes = deckLink.getDisplayModes();
  for(int i = 0; i < displayModes.size(); ++i) {
    printf("Mode %d: %s", i,  displayModes[i].name,
                              displayModes[i].width,
                              displayModes[i].height,
                              displayModes[i].frameRate);
  }
}
