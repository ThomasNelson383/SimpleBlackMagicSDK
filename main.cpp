#include <stdio.h>
#include <stdlib.h>

#include "decklink.h"

int main(void) {
  DeckLink deckLink;

  vector<string> names = deckLink.getDecklinkNames();
  //Making sure there devices to see
  if(names.size() == 0) {
    return -1;
  }
  //Displaying all the names of the Decklinks
  for(unsigned int i = 0; i < names.size(); ++i) {
    printf("Device %d: %s", i, names[i].c_str());
  }
  //Connecting to the first one
  deckLink.connectTo(names[0]);
  //Displaying all the modes
  vector<DeckLink::displayMode> displayModes = deckLink.getOutputModes();
  for(unsigned int i = 0; i < displayModes.size(); ++i) {
    printf("Mode %d: %s, %d, %d", i,  displayModes[i].name.c_str(),
                              displayModes[i].width,
                              displayModes[i].height/*,
                              displayModes[i].frameRate*/);
  }
  return 0;
}
