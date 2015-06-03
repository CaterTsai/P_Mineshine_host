#include "MineshineTheatre.h"

#pragma region Base Method
//--------------------------------------------------------------
void MineshineTheatre::setupTheatre()
{
	_Director.SetStageSize(ofGetWindowWidth(), ofGetWindowHeight());

#pragma region Scenes
	//-------------------------------------------------
	//Scenes
	//-------------------------------------------------
	_Director.AddScenes(NAME_MGR::S_MAIN);
	_Director.AddScenes(NAME_MGR::S_MV);
#pragma endregion

#pragma region Actor
	//-------------------------------------------------
	//Actor
	//-------------------------------------------------
	//S_MAIN
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MAIN_LOOP, "videos/open.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer)));
	_Director.AddActor(new ofxDynamicImageActor(NAME_MGR::A_QR));
	
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MENU_LOOP, "videos/menu.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer), eBLEND_ALPHA));

	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TYPE_HOT_LOOP, "videos/type_hot.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TYPE_WARM_LOOP, "videos/type_warm.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_TYPE_FRESH_LOOP, "videos/type_fresh.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer), eBLEND_ALPHA));
		
	//S_MV
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_1, "mv/1.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_2, "mv/2.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_3, "mv/3.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_4, "mv/4.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_5, "mv/5.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_6, "mv/6.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_7, "mv/7.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_8, "mv/8.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_9, "mv/9.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_10, "mv/10.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_11, "mv/11.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_12, "mv/12.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_13, "mv/13.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));

#pragma endregion

#pragma region Plane
	//-------------------------------------------------
	//Plane
	//-------------------------------------------------
	_Director.AddPlane(NAME_MGR::S_MAIN, NAME_MGR::P_MAIN_OPEN, 0);
	_Director.AddPlane(NAME_MGR::S_MAIN, NAME_MGR::P_MAIN_MENU, 1);
	_Director.AddPlane(NAME_MGR::S_MAIN, NAME_MGR::P_MAIN_TYPE, 2);
	
	_Director.AddPlane(NAME_MGR::S_MV, NAME_MGR::P_MV, 0);
#pragma endregion

#pragma region Element
	//-------------------------------------------------
	//Element
	//-------------------------------------------------
	//S_MAIN
	_Director.AddElement(NAME_MGR::E_MAIN_LOOP, NAME_MGR::P_MAIN_OPEN, NAME_MGR::A_MAIN_LOOP);
	_Director.AddElement(NAME_MGR::E_QR, NAME_MGR::P_MAIN_OPEN, NAME_MGR::A_QR, 1, ofPoint(515, 256), false);
	_Director.AddElement(NAME_MGR::E_MENU_LOOP, NAME_MGR::P_MAIN_MENU, NAME_MGR::A_MENU_LOOP);
	_Director.AddElement(NAME_MGR::E_TYPE_HOT_LOOP, NAME_MGR::P_MAIN_TYPE, NAME_MGR::A_TYPE_HOT_LOOP, 2, ofPoint(0, 0), false);
	_Director.AddElement(NAME_MGR::E_TYPE_WARM_LOOP, NAME_MGR::P_MAIN_TYPE, NAME_MGR::A_TYPE_WARM_LOOP, 3, ofPoint(0, 0), false);
	_Director.AddElement(NAME_MGR::E_TYPE_FRESH_LOOP, NAME_MGR::P_MAIN_TYPE, NAME_MGR::A_TYPE_FRESH_LOOP, 4, ofPoint(0, 0), false);

	//S_MV
	_Director.AddElement(NAME_MGR::E_MV, NAME_MGR::P_MV, NAME_MGR::A_MV_1);
#pragma endregion

#pragma region Translate Element
	
#pragma endregion
	
#pragma region Element setting
	//-------------------------------------------------
	//Element Setting
	//-------------------------------------------------	
	//Video
	ofxVideoElement* pVideoElement_ = nullptr;
	_Director.GetElementPtr(NAME_MGR::E_MAIN_LOOP, pVideoElement_);
	pVideoElement_->SetVideoAutoPlay(true);
	pVideoElement_->SetVideoSubloop(61, false);
	
	_Director.GetElementPtr(NAME_MGR::E_MENU_LOOP, pVideoElement_);
	pVideoElement_->SetVideoAutoPlay(false);
	pVideoElement_->SetVideoSubloop(109, false);

	_Director.GetElementPtr(NAME_MGR::E_TYPE_HOT_LOOP, pVideoElement_);
	pVideoElement_->SetVideoAutoPlay(false);
	pVideoElement_->SetVideoSubloop(76, false);

	_Director.GetElementPtr(NAME_MGR::E_TYPE_WARM_LOOP, pVideoElement_);
	pVideoElement_->SetVideoAutoPlay(false);
	pVideoElement_->SetVideoSubloop(76, false);

	_Director.GetElementPtr(NAME_MGR::E_TYPE_FRESH_LOOP, pVideoElement_);
	pVideoElement_->SetVideoAutoPlay(false);
	pVideoElement_->SetVideoSubloop(76, false);

	_Director.GetElementPtr(NAME_MGR::E_MV, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(true);
	
#pragma endregion

	_bWaitQRCode = true;
	this->setupTimerTrigger();
	this->TheatreAnimInit(NAME_MGR::S_MAIN);
	ofAddListener(ofxTheatreEventArgs::TheatreEvent, this, &MineshineTheatre::onTheatreEvent);
	_Director.Play();
}

//--------------------------------------------------------------
void MineshineTheatre::updateTheatre(float fDelta)
{
	this->updateTimerTrigger(fDelta);
	int iFrame_ = 0;
	
	if(_Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_MAIN)
	{
		ofxVideoElement* ptr_ = nullptr;
		_Director.GetElementPtr(NAME_MGR::E_MAIN_LOOP, ptr_);

		iFrame_ = ptr_->GetFrame();
	}
	_Director.update(iFrame_);
}

//--------------------------------------------------------------
void MineshineTheatre::drawTheatre()
{
	ofPushStyle();
	{
		ofSetColor(255);
		_Director.draw();
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void MineshineTheatre::resetTheatre()
{
	string strEventMsg_ = NAME_MGR::EVENT_Reset;
	ofNotifyEvent(MineshineTheaterEvent, strEventMsg_, this);

	_bWaitQRCode = true;
	_Director.TransitTo(TRANSITION_TYPE::eTRANSITION_FADE);
}

//--------------------------------------------------------------
void MineshineTheatre::nextScence()
{
	if(_Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_MAIN)
	{
		_Director.TransitTo(TRANSITION_TYPE::eTRANSITION_NONE);
	}
	else if(_Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_MV)
	{
		this->resetTheatre();
	}
}

//--------------------------------------------------------------
void MineshineTheatre::TheatreAnimInit(string strName)
{
	ofxBaseElement* pElementPtr_ = nullptr;
	if(strName == NAME_MGR::S_MAIN)
	{
		_Director.GetElementPtr(NAME_MGR::E_QR, pElementPtr_);
		_Director.AddVideoAnimation(NAME_MGR::S_MAIN, new ofxFadeInAnimation(NAME_MGR::ANIM_QREnter, pElementPtr_, 53, 0.0));
	}
	else if(strName == NAME_MGR::AS_HotTypeExit)
	{
		_Director.GetElementPtr(NAME_MGR::E_TYPE_HOT_LOOP, pElementPtr_);
		_Director.AddAnimation(NAME_MGR::S_MAIN, 0, new ofxExitAnimation(NAME_MGR::ANIM_HotTypeExit, pElementPtr_, eExitType::eEXIT_TO_UP, cWINDOW_WIDTH, cWINDOW_HEIGHT));
	}
	else if(strName == NAME_MGR::AS_WarmTypeExit)
	{
		_Director.GetElementPtr(NAME_MGR::E_TYPE_WARM_LOOP, pElementPtr_);
		_Director.AddAnimation(NAME_MGR::S_MAIN, 0, new ofxExitAnimation(NAME_MGR::ANIM_WarmTypeExit, pElementPtr_, eExitType::eEXIT_TO_UP,cWINDOW_WIDTH, cWINDOW_HEIGHT));
	}
	else if(strName == NAME_MGR::AS_FreshTypeExit)
	{
		_Director.GetElementPtr(NAME_MGR::E_TYPE_FRESH_LOOP, pElementPtr_);
		_Director.AddAnimation(NAME_MGR::S_MAIN, 0, new ofxExitAnimation(NAME_MGR::ANIM_FreshTypeExit, pElementPtr_, eExitType::eEXIT_TO_UP,cWINDOW_WIDTH, cWINDOW_HEIGHT));
	}
}

//--------------------------------------------------------------
void MineshineTheatre::onTheatreEvent(ofxTheatreEventArgs& e)
{
	//Scence
	if(e.strMessage == NAME_MGR::S_MAIN)
	{
		this->TheatreAnimInit(NAME_MGR::S_MAIN);
	}

	//Element
	if(e.strMessage == NAME_MGR::E_MV)
	{
		this->addTimerTrigger(
			cWAIT_TO_REST,
			[](MineshineTheatre* Theatre)
			{
				Theatre->resetTheatre();
			}
		);
	}

	//Animation
	if(e.strMessage == NAME_MGR::ANIM_HotTypeExit)
	{
		ofxVideoElement* ptr_ = nullptr;
		_Director.GetElementPtr(NAME_MGR::E_TYPE_HOT_LOOP, ptr_);
		ptr_->StopVideo();
	}
	else if(e.strMessage == NAME_MGR::ANIM_HotTypeExit)
	{
		ofxVideoElement* ptr_ = nullptr;
		_Director.GetElementPtr(NAME_MGR::E_TYPE_WARM_LOOP, ptr_);
		ptr_->StopVideo();
	}
	else if(e.strMessage == NAME_MGR::ANIM_FreshTypeExit)
	{
		ofxVideoElement* ptr_ = nullptr;
		_Director.GetElementPtr(NAME_MGR::E_TYPE_FRESH_LOOP, ptr_);
		ptr_->StopVideo();
	}
}

#pragma endregion

#pragma region QR Code
void MineshineTheatre::setQRCodeImg(ofImage& QRImg)
{
	if(!_bWaitQRCode && _Director.GetNowScenes()->GetScenesName() != NAME_MGR::S_MAIN)
	{
		ofLog(OF_LOG_ERROR, "[MineshineTheatre:setQRCodeImg] _bWaitQRCode is false");
		return;
	}

	ofxDynamicImageElement* pQRImg_ = nullptr;
	_Director.GetElementPtr(NAME_MGR::E_QR, pQRImg_);
	pQRImg_->updateImg(QRImg);
	_bWaitQRCode = false;
}
#pragma endregion

#pragma region MV
bool MineshineTheatre::setMV(int iSongID)
{
	if(iSongID <= 0 || iSongID > cSONG_NUM)
	{
		return false;
	}
	ofxVideoElement* pMV_ = nullptr;
	_Director.GetElementPtr(NAME_MGR::E_MV, pMV_);
	pMV_->ChangeVideoActor(dynamic_cast<ofxVideoActor*>(_Director.GetActor("A_MV_" + ofToString(iSongID) )));
	return true;
}
#pragma endregion

#pragma region Timer Trigger
void MineshineTheatre::setupTimerTrigger()
{
	_fTimer = .0;
	_bEnableTimer = false;
}

//-------------------------------------------------
void MineshineTheatre::updateTimerTrigger(float fDelta)
{
	if(_bEnableTimer)
	{
		_fTimer -= fDelta;

		if(_fTimer < 0.0)
		{
			_bEnableTimer = false;
			_trigger(this);
		}
	}
}

//-------------------------------------------------
void MineshineTheatre::addTimerTrigger(float fTimer, function<void(MineshineTheatre*)> triggerEvent )
{
	if(!_bEnableTimer)
	{
		_fTimer = fTimer;
		_trigger = triggerEvent;
		_bEnableTimer = true;
	}
}

//-------------------------------------------------
void MineshineTheatre::removeTimerTrigger()
{
	if(_bEnableTimer)
	{
		_fTimer = .0;
		_bEnableTimer = false;
	}
}
#pragma endregion
