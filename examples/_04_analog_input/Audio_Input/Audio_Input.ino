/*  Test of audio input using Mozzi sonification library.
 
 An audio input using the range between 0 to 5V on analog pin A0
 is sampled and output on digital pin 9.
 
 Configuration: requires "#define USE_AUDIO_INPUT true" to be in
 Mozzi/mozzi_config.h file.
 
 Circuit: 
 Audio cable centre wire on pin A0, outer shielding to Arduino Ground.
 Audio output on digital pin 9 (on a Uno or similar), or
 check the README or http://sensorium.github.com/Mozzi/
 
 Mozzi help/discussion/announcements:
 https://groups.google.com/forum/#!forum/mozzi-users
 
 */

#include <MozziGuts.h>

void setup(){
  startMozzi();
}


void updateControl(){
}


int updateAudio(){
  int asig = getAudioInput(); // range 0-1023
  asig = asig - 512; // now range is -512 to 511
  // output range in STANDARD mode is -244 to 243, 
  // so you might need to adjust your signal to suit
  return asig;
}


void loop(){
  audioHook();
}




