#include "MineshineHost.h"

#pragma region Base function
//--------------------------------------------------------------
void MineshineHost::setup()
{
	ofBackground(0);
	ofSetVerticalSync(true);

	ofLogToFile(ofGetTimestampString("Log_%m%d.txt"), true);

	//loading config file
	if(!this->loadconfig())
	{
		getchar();
		std::exit(-1);
	}

	//BGM
	this->setupBGM();
	_BGM.play();

	//DB Connector
	this->setupDBConnector();

	//Theatre
	this->initTheatre();
	
	//initial
	this->reset();

	//slack reporter initial
	if(_exSlack)
	{
		_Slack.setup();
	}
	_Slack.Report("[Slack] Program start, Host ID:" + ofToString(_exHostID));
	_fKeepAlive = cKEEP_ALIVE_TIMER;

	_fCheckTimer = cCHECK_TIME;
	_fMainTimer = ofGetElapsedTimef();

	_bShowMouse = false;
	ofHideCursor();
	ofToggleFullscreen();
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

	//BGM
	this->updateBGM(fDelta_);

	//Keep Alive
	_fKeepAlive -= fDelta_;
	if(_fKeepAlive <= 0.0)
	{
		_Slack.Report("[KEEP-ALIVE]Host ID:" + ofToString(_exHostID));
		_fKeepAlive = cKEEP_ALIVE_TIMER;
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
void MineshineHost::exit()
{
	_DBConnector.stop();
	_Slack.exit();
}

//--------------------------------------------------------------
void MineshineHost::reset()
{	
	_iNowState = 0;
	_iNextState = _iSongID = _iType = -1;
	_bIsCheckQRCodeOK = false;
	_TimeKey =  ofToString(_exHostID) + ofGetTimestampString("%d%H%M%S");
	this->addNewQRCode();
	this->FadeinBGM();
}

//--------------------------------------------------------------
void MineshineHost::keyPressed(int key)
{
	switch(key)
	{
	case 'r':
		{
			_Theatre.CanSetQR();
			this->reset();
			break;
		}
	case 'f':
		{
			_bShowMouse?ofHideCursor():ofShowCursor();
			_bShowMouse ^= true;

			ofToggleFullscreen();
			break;
		}
	}
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
	if(e == NAME_MGR::EVENT_Reset)
	{
		this->reset();
	}
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
				
				ofxVideoElement* ptr_ = nullptr;
				_Theatre._Director.GetElementPtr(NAME_MGR::E_MENU_LOOP, ptr_);
				ptr_->PlayVideo();
				break;
			}
			if(_exCanSkip && _iNextState == 3  && _Theatre.setMV(_iSongID))
			{
				_iNowState = _iNextState;
				_Theatre.nextScence();
				this->FadeoutBGM();
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
						ofxVideoElement* ptr_ = nullptr;
						_Theatre._Director.GetElementPtr(NAME_MGR::E_TYPE_HOT_LOOP, ptr_);
						ptr_->SetVisible(true);
						ptr_->PlayVideo();
					}
					break;
				case 2:
					{
						ofxVideoElement* ptr_ = nullptr;
						_Theatre._Director.GetElementPtr(NAME_MGR::E_TYPE_WARM_LOOP, ptr_);
						ptr_->SetVisible(true);
						ptr_->PlayVideo();
					}
					break;
				case 3:
					{
						ofxVideoElement* ptr_ = nullptr;
						_Theatre._Director.GetElementPtr(NAME_MGR::E_TYPE_FRESH_LOOP, ptr_);
						ptr_->SetVisible(true);
						ptr_->PlayVideo();
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
				this->FadeoutBGM();
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

#pragma region BGM
void MineshineHost::setupBGM()
{
	_BGM.loadSound("audios/bgm.mp3");
	_BGM.setLoop(true);
	_BGM.setVolume(0.0);

	_bFade = false;
	_AnimVol.setDuration(cBGM_FADE_TIME);
	_AnimVol.reset(0.0);
}

//--------------------------------------------------------------
void MineshineHost::updateBGM(float fDelta)
{
	_AnimVol.update(fDelta);

	if(_bFade)
	{
		_BGM.setVolume(_AnimVol.getCurrentValue());

		if(_AnimVol.hasFinishedAnimating() && _AnimVol.getPercentDone() == 1.0)
		{
			_bFade = false;
		}
	}
}

//--------------------------------------------------------------
void MineshineHost::FadeoutBGM()
{
	_bFade = true;
	_AnimVol.animateFromTo(1.0, 0.0);
}

//--------------------------------------------------------------
void MineshineHost::FadeinBGM()
{
	_bFade = true;
	_AnimVol.animateFromTo(0.0, 1.0);
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
	_exCanSkip = (config_.getValue("CAN_SKIP", 0, 0) == 1);
	_exSlack = (config_.getValue("SLACK", 0, 0) == 1);

	if(_exHostID == -1 || _exMobileUrl == "" || _exActiveUrl == "")
	{
		return false;
	}
	return true;
}
#pragma endregion