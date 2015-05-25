#include "MineshineHost.h"

#pragma region Base function
//--------------------------------------------------------------
void MineshineHost::setup()
{
	ofBackground(0);
	ofSetVerticalSync(true);

	//loading config file
	if(!this->loadconfig())
	{
		getchar();
		std::exit(-1);
	}

	//DB Connector
	_iNowState = 0;
	_iNextState = _iSongID = _iType = -1;
	_bIsCheckQRCodeOK = false;
	this->setupDBConnector();
	_TimeKey =  ofToString(_exHostID) + ofGetTimestampString("%m%d%H%M");
	this->addNewQRCode();

	//Theatre
	this->initTheatre();
	
	_fMainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void MineshineHost::update()
{
	float fDelta_ = ofGetElapsedTimef() - _fMainTimer;
	_fMainTimer += fDelta_;

	//Set qr code
	if(_bIsCheckQRCodeOK && _Theatre.CanSetQR())
	{
		if(_QRCode.IsGotQR())
		{
			_Theatre.setQRCodeImg(_QRCode);
		}
	}

	//Check state
	_fCheckTimer -= fDelta_;
	if(_fCheckTimer <= 0.0)
	{
		this->stateCheck();
		_fCheckTimer = cCHECK_TIME;
	}
	

	_Theatre.updateTheatre(fDelta_);

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void MineshineHost::draw()
{
	_Theatre.drawTheatre();
}

//--------------------------------------------------------------
void MineshineHost::keyPressed(int key)
{
	switch(key)
	{
	case 'q':
		{
			_TimeKey = ofGetTimestampString("%m%d%H%M") + ofToString(_exHostID);
			this->addNewQRCode();
			break;
		}
	}
}

//--------------------------------------------------------------
void MineshineHost::exit()
{
	_DBConnector.stop();
}

#pragma endregion

#pragma region Theatre
void MineshineHost::initTheatre()
{
	_Theatre.setupTheatre();
	ofAddListener(_Theatre.MineshineTheaterEvent, this, &MineshineHost::onTheatreEvent);
}

//--------------------------------------------------------------
void MineshineHost::drawBeforeTheatre()
{

}

//--------------------------------------------------------------
void MineshineHost::drawAfterTheatre()
{

}

//--------------------------------------------------------------
void MineshineHost::onTheatreEvent(string& e)
{

}

//--------------------------------------------------------------
void MineshineHost::stateCheck()
{
	bool bNeedCatchState_ = false;
	switch(_iNowState)
	{
	case 0:
		{
			if(_iNextState == 1)
			{
				_iNowState = _iNextState;
				_Theatre.nextScence();
				break;
			}
			bNeedCatchState_ = true;
		}
		break;
	case 1:
		{
			if(_iNextState == 2)
			{
				
				switch(_iType)
				{
				case 1:
					{	
						_Theatre.TheatreAnimInit(NAME_MGR::AS_HotTypeEnter);
					}
					break;
				case 2:
					{
						_Theatre.TheatreAnimInit(NAME_MGR::AS_WarmTypeEnter);
					}
					break;
				case 3:
					{
						_Theatre.TheatreAnimInit(NAME_MGR::AS_FreshTypeEnter);
					}
					break;
				default:
					{
						ofLog(OF_LOG_ERROR, "[MineshineHost:stateCheck] Unknow Type");
						return;
					}
				}
				
				_TmpType = _iType;
				_iNowState = _iNextState;
			}

			bNeedCatchState_ = true;
		}
		break;
	case 2:
		{	//back
			if(_iNextState == 1)
			{
				switch(_TmpType)
				{
				case 1:
					{
						_Theatre.TheatreAnimInit(NAME_MGR::AS_HotTypeExit);
					}
					break;
				case 2:
					{
						_Theatre.TheatreAnimInit(NAME_MGR::AS_WarmTypeExit);
					}
					break;
				case 3:
					{
						_Theatre.TheatreAnimInit(NAME_MGR::AS_FreshTypeExit);
					}
					break;
				default:
					{
						ofLog(OF_LOG_ERROR, "[MineshineHost:stateCheck] Unknow Type");						
						return;
					}
				}
				_iNowState = _iNextState;
				break;
				
			}


			if(_iNextState == 3 && _Theatre.setMV(_iSongID))
			{
				_iNowState = _iNextState;
				_Theatre.nextScence();
				break;
			}
			bNeedCatchState_ = true;
		}
		break;
	case 3:
		{
			bNeedCatchState_ = false;
		}
		break;
	}

	if(bNeedCatchState_)
	{
		this->getInfo();
	}
}
#pragma endregion

#pragma region DB connection
void MineshineHost::setupDBConnector()
{
	ofAddListener(_DBConnector.newResponseEvent, this, &MineshineHost::onHttpResponse);
	_DBConnector.start();
}

//--------------------------------------------------------------
void MineshineHost::addNewQRCode()
{
	if(_TimeKey == "")
	{
		return;
	}
	_bIsCheckQRCodeOK = false;
	ofxHttpForm	HttpForm_;
	HttpForm_.action = _exActiveUrl + "?active=" + cADD_NEW_QRCODE + "&key=" + _TimeKey + "&host=" + ofToString(_exHostID);
	HttpForm_.method = OFX_HTTP_GET;

	_DBConnector.addForm(HttpForm_);
}

//--------------------------------------------------------------
void MineshineHost::getInfo()
{
	ofxHttpForm	HttpForm_;
	HttpForm_.action = _exActiveUrl + "?active=" + cCHECK_DB + "&key=" + _TimeKey;
	HttpForm_.method = OFX_HTTP_GET;

	_DBConnector.addForm(HttpForm_);
}

//--------------------------------------------------------------
void MineshineHost::onHttpResponse(ofxHttpResponse& response)
{
	Json::Value Root_;
	Json::Reader JsonReader_;

	JsonReader_.parse(response.responseBody.getText(), Root_);

	string Active_ = Root_.get("name", "").asString();
	
	if(Active_ == cADD_NEW_QRCODE)
	{
		_bIsCheckQRCodeOK = Root_.get("result", false).asBool();
		if(_bIsCheckQRCodeOK)
		{
			ofLog(OF_LOG_NOTICE, "[MineshineHost]key check ok!! request qr code :" + ofToString(_TimeKey));
			_QRCode.fetch(_exMobileUrl + _TimeKey, cQR_SIZE);
		}
	}
	else if(Active_ == cCHECK_DB)
	{
		_iNextState = ofToInt(Root_.get("state", "").asString());
		_iType = ofToInt(Root_.get("type", "").asString());
		_iSongID = ofToInt(Root_.get("song_id", "").asString());
	}
	else
	{
		ofLog(OF_LOG_WARNING, "[MineshineHost]Unknow active name : " + Active_);
	}
}
#pragma endregion

#pragma region Config file
bool MineshineHost::loadconfig()
{
	ofxXmlSettings	config_;
	if(!config_.loadFile("_config.xml"))
	{
		ofLog(OF_LOG_ERROR, "[Config file]Load config.xml failed");
		return false;
	}

	_exHostID = config_.getValue("HOSTID", -1, 0);
	_exMobileUrl = config_.getValue("MOBILE_URL", "", 0);
	_exActiveUrl = config_.getValue("ACTIVE_URL", "", 0);


	if(_exHostID == -1 || _exMobileUrl == "" || _exActiveUrl == "")
	{
		return false;
	}
	return true;
}
#pragma endregion