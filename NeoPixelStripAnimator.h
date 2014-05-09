#include <Adafruit_NeoPixel.h>


//////////////////////////////////////////////////////////////////////
// INeoPixelAnimation - This is the interface for all the animations

class INeoPixelAnimation {
  public:
    virtual void setup(Adafruit_NeoPixel *strip) = 0;
    virtual void loop() = 0;
    virtual bool isDone() = 0;
};


/////////////////////////////////////////////////////////////////////////////////
// NeoPixelStripAnimator - The main controller for neopixel strip animations

class NeoPixelStripAnimator {
  public:
    NeoPixelStripAnimator(Adafruit_NeoPixel* strip);
    void setup();
    void loop();
    void startAnimation(INeoPixelAnimation *animation);
    bool isAnimationRunnning();
    void clear();

  private:
      Adafruit_NeoPixel *_strip;
      INeoPixelAnimation *_currentAnimation;
};


/////////////////////////////////////////////////////////////////////////////////
// ColorWipeAnimation - It lights up pixels one by one on the given color

class ColorWipeAnimation : public INeoPixelAnimation {
  public:
    ColorWipeAnimation(uint32_t color, int pixelInterval);
    virtual void loop();
    virtual bool isDone();
    virtual void setup(Adafruit_NeoPixel *strip);

  private:
    unsigned long _lastTimeCheck;
    unsigned long _pixelInterval;
    Adafruit_NeoPixel *_strip;
    bool _done;
    unsigned int _currentPixel;
    uint32_t _color;

};


/////////////////////////////////////////////////////////////////////////////////
// NightRiderAnimation - David Hasselhof not included

class NightRiderAnimation : public INeoPixelAnimation {
  public:
    NightRiderAnimation(uint32_t color, int pixelInterval);
    virtual void loop();
    virtual bool isDone();
    virtual void setup(Adafruit_NeoPixel *strip);
  private:
    uint32_t _color;
    bool _done;
    int _currentPixel;
    unsigned long _pixelInterval;
    unsigned long _lastTimeCheck;
    short _delta;
    Adafruit_NeoPixel *_strip;
};


