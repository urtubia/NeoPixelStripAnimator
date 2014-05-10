#include "NeoPixelStripAnimator.h"

//////////////////////////////////////////////////////////////////////
// NeoPixelStripAnimator

NeoPixelStripAnimator::NeoPixelStripAnimator(Adafruit_NeoPixel* strip)
{
  _strip = strip;
  _currentAnimation = NULL;
}

void NeoPixelStripAnimator::setup()
{
  _strip->begin();
  _strip->show(); // Initialize all pixels to 'off'
}

void NeoPixelStripAnimator::loop()
{
  if(isAnimationRunnning()){
    _currentAnimation->loop();
    if(_currentAnimation->isDone()){
      delete _currentAnimation;
      _currentAnimation = NULL;
    }
  }
}

void NeoPixelStripAnimator::startAnimation(INeoPixelAnimation *animation)
{
  if(_currentAnimation != NULL)
    delete _currentAnimation;
  _currentAnimation = animation;
  _currentAnimation->setup(_strip);
}

bool NeoPixelStripAnimator::isAnimationRunnning()
{
  return _currentAnimation != NULL;
}

void NeoPixelStripAnimator::clear()
{
  if(_currentAnimation != NULL) delete _currentAnimation;
  _currentAnimation = NULL;
  for(int i = 0; i < _strip->numPixels(); i++){
    _strip->setPixelColor(i, Adafruit_NeoPixel::Color(0,0,0));
  }
  _strip->show(); // Initialize all pixels to 'off'
}


//////////////////////////////////////////////////////////////////////
// ColorWipeAnimation

ColorWipeAnimation::ColorWipeAnimation(uint32_t color, int pixelInterval)

{
  _lastTimeCheck = millis();
  _done = false;
  _currentPixel = -1;
  _pixelInterval = pixelInterval;
  _color = color;
}

void ColorWipeAnimation::setup(Adafruit_NeoPixel *strip)
{
  _strip = strip;
  for(int i = 0; i < _strip->numPixels();i++){
      _strip->setBrightness(255);
    }

}


void ColorWipeAnimation::loop()
{
  if(_done) return;
  unsigned long now = millis();
  if((now - _lastTimeCheck) > _pixelInterval){
    _currentPixel++;
    if(_currentPixel >= _strip->numPixels()){
      _done = true;
      return;
    }
    _strip->setPixelColor(_currentPixel, _color);
    _strip->show();
    _lastTimeCheck = now;
  }
}

bool ColorWipeAnimation::isDone()
{
  return _done;
}


//////////////////////////////////////////////////////////////////////
// NightriderAnimation

NightRiderAnimation::NightRiderAnimation(uint32_t color, int pixelInterval)

{
  _lastTimeCheck = millis();
  _done = false;
  _currentPixel = -1;
  _pixelInterval = pixelInterval;
  _color = color;
  _delta = 1;
}

void NightRiderAnimation::setup(Adafruit_NeoPixel *strip)
{
  _strip = strip;
  _strip->setBrightness(255);
}


void NightRiderAnimation::loop()
{
  unsigned long now = millis();
  if((now - _lastTimeCheck) > _pixelInterval){
    _currentPixel += _delta;
    if(_currentPixel == _strip->numPixels()){
      _delta = -1;
    }else if(_currentPixel == -1){
      _delta = 1;
    }
    for(int i = 0; i < _strip->numPixels(); i++){
      if(_currentPixel == i){
        _strip->setPixelColor(i, _color);
      }else{
        _strip->setPixelColor(i, Adafruit_NeoPixel::Color(0,0,0));
      }
    }
    _strip->show();
    _lastTimeCheck = now;
  }
}

bool NightRiderAnimation::isDone()
{
  return _done;
}

/////////////////////////////////////////////////////////////////////////////////////
// FadeOutAnimation - It will linearly decrease the brightness of the given color.

FadeOutAnimation::FadeOutAnimation(uint32_t color, int millisToFadeOut)
{
  _lastTimeCheck = millis();
  _done = false;
  _millisToFadeOut = millisToFadeOut;
  _currentBrightness = 255;
  _color = color;
  _done = false;
}

void FadeOutAnimation::setup(Adafruit_NeoPixel *strip)
{
  _strip = strip;
  _deltaBrightnessDecrease = (unsigned long)(_millisToFadeOut / 255.0);
}

void FadeOutAnimation::loop()
{
  if(isDone()) return;

  unsigned long now = millis();
  if((now - _lastTimeCheck) > _deltaBrightnessDecrease){
    _currentBrightness--;
    for(int i = 0; i < _strip->numPixels();i++){
      _strip->setPixelColor(i, _color);
      _strip->setBrightness(_currentBrightness);
    }
    _strip->show();
    _lastTimeCheck = now;
    if(_currentBrightness < 1){
      _done = true;
    }
  }
}

bool FadeOutAnimation::isDone()
{
  return _done;
}
