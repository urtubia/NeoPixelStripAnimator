# NeoPixel Strip Animator
This is an Arduino library and a Pinoccio sketch that makes animating NeoPixel strands in a non-blocking way as easy as possible. The main motivation for this is that to take full advantage of platforms like the *Pinoccio*, we need to let the main loop run freely (no blocking delays), so that the board can take care of other things like network and serial communications.

## Requirements
* The library requires the Adafruit Neopixel library, available in here: https://github.com/adafruit/Adafruit_NeoPixel
* The Pinoccio sketch (`examples\PinoccioPixels`) requires the right version of the Arduino IDE and the pinoccio-firmware libraries. More information in here: https://pinocc.io/solo

## Installation
Copy the contents of this repo into:
(YOUR_ARDUINO_DOCS)/libraries/NeoPixelStripAnimator/

## Pinoccio ScoutScript integration

The included Pinoccio sketch adds the following ScoutScript commands (pull requests for more pixel animations welcome!)

    pixels.clear
    pixels.redwipe
    pixels.greenwipe
    pixels.bluewipe
    pixels.nightrider
    pixels.fadeout
    
For a quick video demo see: https://plus.google.com/103920799952529517985/posts/avoH1sf18kK

On the video, I'm using 6 Flora RGB NeoPixels sewed into a (super awesome, Internet-aware) necktie. 

## Using the library

The following is a simple Arduino sketch that will use the library cycle between the "NightRider" animation and clearing the strip for each byte received on the serial port.

    #include <Adafruit_NeoPixel.h>
    #include <NeoPixelStripAnimator.h>
    
    #define PIN 6
    
    // Declare and configure the NeoPixel strand
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, PIN, NEO_GRB + NEO_KHZ800);
    // Declare and configure the animator
    NeoPixelStripAnimator neoPixelStripAnimator(&strip);
    
    int state = 0;
    void setup() {
        Serial.begin(9600);
        neoPixelStripAnimator.setup();
    }
    
    void loop() {
        neoPixelStripAnimator.loop();
        if (Serial.available() > 0) {
            Serial.read();
            state = (state + 1) % 2;
            if(state){
                neoPixelStripAnimator.startAnimation(new NightRiderAnimation(Adafruit_NeoPixel::Color(255,0,0), 70));
            }else{
                neoPixelStripAnimator.clear();
            }
        }
    }
    
## Author

Hector Urtubia, hector@bigrobotstudios.com

## License

NeoPixelStripAnimator is available under the MIT license. See the LICENSE file for more info.

    
