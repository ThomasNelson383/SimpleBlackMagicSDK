#include "decklink.h"

DeckLink::~DeckLink() {
  close();
}
DeckLink() {
  deckLInk = NULL;
}
DeckLink(const string &nameOfDevice) {
  deckLink = NULL;
  connectTo(nameOfDevice);
}

bool isOpen() {
  return deckLink;
}
bool connectTo(const string &nameOfDevice) {
  vector<string>      names;
  IDeckLinkIterator*	deckLinkIterator = CreateDeckLinkIteratorInstance();
  IDeckLink*				  deckLinkTemp;

  if(isOpen()) {
    close();
  }

  if(deckLinkIterator == NULL) {
    //Couldn't create an iterator.
    //The Decklink drives may not be installed
    return names;
  }

  while(deckLinkIterator->Next(&deckLink) == S_OK) {
    char *nameTemp = NULL;
    deckLinkTemp->GetModelName((const char **) &deviceNameString);
    HRESULT result = deckLink->GetModelName((const char **) &name);

    if(result == s_ok &&
      nameOfDevice.compare(nameTemp) == 0) {
      deckLink = deckLink;
      return true;
    }
    delete nameTemp;
    deckLink->Release();
  }
  deckLinkIterator->Release();
  return false;
}
void close() {
  if(deckLInk) {
    deckLink->Release();
    deckLInk = NULL;
  }
}

vector<displayMode> getOutputModes() {
  IDeckLinkOutput*					     deckLinkOutput = NULL;
	IDeckLinkDisplayModeIterator*	 displayModeIterator = NULL;
	IDeckLinkDisplayMode*				   displayMode = NULL;

  std::vector<displayMode> displayModes;

  // Query the DeckLink for its configuration interface
  result = deckLink->QueryInterface(IID_IDeckLinkOutput, (void**)&deckLinkOutput);
  if (result != S_OK) {
    //Couldn't open deckLinkOutput
    return displayModes;
  }
  // Obtain an IDeckLinkDisplayModeIterator to enumerate the display modes supported on output
  result = deckLinkOutput->GetDisplayModeIterator(&displayModeIterator);
  if (result != S_OK) {
    //"Could not obtain the video output display mode iterator
    deckLinkOutput->Release();
    return displayModes;
  }
  while (displayModeIterator->Next(&displayMode) == S_OK) {
		char *displayModeString = NULL;

		result = displayMode->GetName((const char **) &displayModeString);
		if (result == S_OK) {
      displayMode mode;
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

vector<string> DeckLink::getDecklinkNames() {
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
    deckLink->GetModelName((const char **) &deviceNameString);
    HRESULT result = deckLink->GetModelName((const char **) &name);

    if(result == s_ok) {
      names.push_back(name);
    }
    delete name;
    deckLink->Release();
  }

  deckLinkIterator->Release();
  return names;
}
