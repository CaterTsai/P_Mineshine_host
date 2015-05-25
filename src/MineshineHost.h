#pragma once

#include "../json/json.h"

#include "ofxXmlSettings.h"
#include "ofxHttpUtils.h"
#include "ofxQRcode.h"

#include "constParameter.h"
#include "MineshineTheatre.h"

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

	void keyPressed(int key);

private:
	string	_TimeKey;
	float	_fMainTimer;
//-------------------------------------------------
//Theatre
//-------------------------------------------------
private:
	void initTheatre();
	void drawBeforeTheatre();
	void drawAfterTheatre();
	void onTheatreEvent(string& e);
	
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
		
	void stateCheck();
private:
	int				_iNowState, _iNextState, _iSongID, _iType;
	int				_TmpType;
	bool			_bIsCheckQRCodeOK;
	ofxHttpUtils	_DBConnector;

	float			_fCheckTimer;
	ofxQRcode		_QRCode;

//-------------------------------------------------
//Config file
//-------------------------------------------------
public:
	bool loadconfig();

private:
	int	_exHostID;
	string	_exMobileUrl;
	string	_exActiveUrl;
};
