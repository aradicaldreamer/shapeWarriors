#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// listen on port 8888
#define PORT 8888
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp {
	public:

		void setup();
		void update();
		void draw();
        void drawPlayers();
        void keyPressed(int key);
        void drawShapes();
        
		ofxOscReceiver receiver;
        deque<string> messageBuffer;
        int maxBufferSize=20;
    
        // Importing OSC data into game state
        string deviceID;
        int xPos, yPos;
        deque<ofPoint> points_1;
        deque<ofPoint> points_2;
        deque<ofPoint> points_3;
        deque<ofPoint> points_4;
    
        ofPoint pt1, pt2, pt3, pt4;
    
        ofColor color1, color2, color3, color4;
    
        int fadeOut;
        bool timer;
        bool drawImage, shapes, players;
        float phase;
    
        ofImage background_image;
        string background;
    
};
