#pragma once

#include "../json/json.h"

#include "ofxXmlSettings.h"
#include "ofxHttpUtils.h"
#include "ofxQRcode.h"
#include "ofxAnimatableFloat.h"

#include "constParameter.h"
#include "MineshineTheatre.h"
#include "SlackReporter.h"

#ifdef _DEBUG
	#ifndef _JSON
		#define _JSON
		#pragma comment(lib,"json/lib/lib_json_debug.lib")
	#endif //_JSON
#else //_DEBUG
	#ifndef _JSON
		#define _JSON
		#pragma comment(lib,"json/lib/lib_json.lib")
	#endif //_JSON
#endif //_DEBUG

class MineshineHost : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	void reset();

	void keyPressed(int key);

private:
	bool	_bShowMouse;
	string	_TimeKey;
	float	_fMainTimer;
	float	_fTimeout;
//-------------------------------------------------
//Theatre
//-------------------------------------------------
private:
	void initTheatre();
	void drawBeforeTheatre();
	void drawAfterTheatre();
	void onTheatreEvent(string& e);
	void stateCheck();
private:
	MineshineTheatre	_Theatre;

//-------------------------------------------------
//DB Connection (PHP)
//-------------------------------------------------
public:
	void setupDBConnector();
	void addNewQRCode();
	void getInfo();
	void onHttpResponse(ofxHttpResponse& response);
	
private:
	int				_iNowState, _iNextState, _iSongID, _iType;
	int				_TmpType;
	bool			_bIsCheckQRCodeOK;
	ofxHttpUtils	_DBConnector;

	float			_fCheckTimer;
	ofxQRcode		_QRCode;

//-------------------------------------------------
//BGM
//-------------------------------------------------
public:
	void setupBGM();
	void updateBGM(float fDelta, bool bUpdate = true);
	void stopBGM();
	void resetBGM();

private:
	void FadeoutBGM();
	void FadeinBGM();

private:
	bool				_bIsMineshineMusic, _bFade;
	float				_fBGMTimer;
	ofxAnimatableFloat	_AnimVol;

	ofSoundPlayer		_BGM, _MineshineMusic;

//-------------------------------------------------
//Slack
//-------------------------------------------------
public:
	float			_fKeepAlive;
	SlackReporter	_Slack;

//-------------------------------------------------
//Config file
//-------------------------------------------------
public:
	bool loadconfig();

private:
	int	_exHostID;
	string	_exMobileUrl;
	string	_exActiveUrl;
	bool	_exCanSkip;
	bool	_exSlack;
};
