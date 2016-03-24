#include "decklink.h"

DeckLink::~DeckLink() {
  close();
}
DeckLink::DeckLink() {
  BMDeckLink = NULL;
}
DeckLink::DeckLink(const string &nameOfDevice) {
  BMDeckLink = NULL;
  connectTo(nameOfDevice);
}

bool DeckLink::isOpen() {
  return BMDeckLink;
}
bool DeckLink::connectTo(const string &nameOfDevice) {
  vector<string>      names;
  IDeckLinkIterator*	deckLinkIterator = CreateDeckLinkIteratorInstance();
  IDeckLink*				  deckLinkTemp;

  if(isOpen()) {
    close();
  }

  if(deckLinkIterator == NULL) {
    //Couldn't create an iterator.
    //The Decklink drives may not be installed
    return false;
  }

  while(deckLinkIterator->Next(&deckLinkTemp) == 0) {
    char *nameTemp = NULL;  
    int result = deckLinkTemp->GetModelName((const char **) &nameTemp);
    

    if(result == 0 &&
      nameOfDevice.compare(nameTemp) == 0) {
      BMDeckLink = deckLinkTemp;
      return true;
    }
    delete nameTemp;
    deckLinkTemp->Release();
  }
  deckLinkIterator->Release();
  return false;
}
void DeckLink::close() {
  if(isOpen()) {
    BMDeckLink->Release();
    BMDeckLink = NULL;
  }
}

vector<DeckLink::displayMode> DeckLink::getOutputModes() {
  IDeckLinkOutput*					     deckLinkOutput = NULL;
	IDeckLinkDisplayModeIterator*	 displayModeIterator = NULL;
	IDeckLinkDisplayMode*				   displayMode = NULL;

  std::vector<DeckLink::displayMode> displayModes;

  // Query the DeckLink for its configuration interface
  int result = BMDeckLink->QueryInterface(IID_IDeckLinkOutput, (void**)&deckLinkOutput);
  if (result != 0) {
    //Couldn't open deckLinkOutput
    return displayModes;
  }
  // Obtain an IDeckLinkDisplayModeIterator to enumerate the display modes supported on output
  result = deckLinkOutput->GetDisplayModeIterator(&displayModeIterator);
  if (result != 0) {
    //"Could not obtain the video output display mode iterator
    deckLinkOutput->Release();
    return displayModes;
  }
  while (displayModeIterator->Next(&displayMode) == S_OK) {
		char *displayModeString = NULL;

    result = displayMode->GetName((const char **) &displayModeString);
    if (result == S_OK) {
      DeckLink::displayMode mode;
      mode.name = displayModeString;
      mode.width = displayMode->GetWidth();
      mode.height = displayMode->GetHeight();
      //displayMode->GetFrameRate(&frameRateDuration, &frameRateScale);
      displayModes.push_back(mode);
    }
    displayMode->Release();
  }
  displayModeIterator->Release();
  deckLinkOutput->Release();

  return displayModes;
}

vector<string> DeckLink::DeckLink::getDecklinkNames() {
  vector<string> names;
  IDeckLinkIterator*	deckLinkIterator = CreateDeckLinkIteratorInstance();
  IDeckLink*				deckLink;

  if(deckLinkIterator == NULL) {
    //Couldn't create an iterator.
    //The Decklink drives may not be installed
    return names;
  }

  while(deckLinkIterator->Next(&deckLink) == S_OK) {
    char *name = NULL;
    int result = deckLink->GetModelName((const char **) &name);

    if(result == 0) {
      names.push_back(name);
    }
    delete name;
    deckLink->Release();
  }

  deckLinkIterator->Release();
  return names;
}
