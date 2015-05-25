#ifndef MINESHINE_THEATRE
#define MINESHINE_THEATRE

#include "constParameter.h"
#include "ofxTheatreDirector.h"
#include "ofGstVideoPlayer.h"
#include "ofxHapPlayer.h"

class MineshineTheatre
{
public:
	void setupTheatre();
	void updateTheatre(float fDelta);
	void drawTheatre();
	void resetTheatre();

	void nextScence();

	void TheatreAnimInit(string strName);
	void onTheatreEvent(ofxTheatreEventArgs& e);

public:
	ofxDirector		_Director;

//-------------------------------
// QR Code
//-------------------------------
public:
	void setQRCodeImg(ofImage& QRImg);
	
public:
	inline bool CanSetQR()
	{
		return _bWaitQRCode && _Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_MAIN;
	}

private:
	bool	_bWaitQRCode;

//-------------------------------
// MV
//-------------------------------
public:
	bool setMV(int iSongID);

//-------------------------------
// Timer Trigger
//-------------------------------
private:
	void setupTimerTrigger();
	void updateTimerTrigger(float fDelta);

	void addTimerTrigger(float fTimer, function<void(MineshineTheatre*)> triggerEvent );	
	void removeTimerTrigger();
private:
	bool								_bEnableTimer;
	float								_fTimer;
	function<void(MineshineTheatre*)>	_trigger;

//-------------------------------
//Theatre Event
//-------------------------------
public:
	ofEvent<string>	MineshineTheaterEvent;
};

#endif // !MINESHINE_THEATRE
