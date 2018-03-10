#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

    fadeOut = 100;
	ofBackground(255);
    background_image.load("background.jpg");
    timer = false;
    drawImage = false;
    shapes = false;
    players = false;
    
    color1 = ofColor(0,0,0);
    color2 = ofColor::red;
    color3 = ofColor::darkGreen;
    color4 = ofColor::blue;
}

//--------------------------------------------------------------
void ofApp::update(){
    
        if (messageBuffer.size()>maxBufferSize) messageBuffer.pop_back();

        // check for waiting messages
        while(receiver.hasWaitingMessages()){
            // get the next message
            ofxOscMessage m;
            receiver.getNextMessage(m);

            // check for mouse moved message
            if(m.getAddress() == "/position"){
                for (int i = 0; i < m.getNumArgs(); i += 3) {
                    deviceID = m.getArgAsString(i);
                    int x = m.getArgAsInt(i+1);
                    xPos = ofMap(x, 0, 10420, 0, ofGetWidth());
                    int y = m.getArgAsInt(i+2);
                    yPos = ofMap(y, 0, 12160, 0, ofGetHeight());
                    ofPoint pt;
                    
                    if(deviceID == "28168"){ // this is our piece
                        pt.set(xPos,yPos);
                        pt1 = pt;
                        points_1.push_back(pt);
                    }
                    
                    if(deviceID == "26954"){ // this is our piece
                        pt.set(xPos,yPos);
                        pt2 = pt;
                        points_2.push_back(pt);
                    }
                    
                    if(deviceID == "26996"){ // this is our piece
                        pt.set(xPos,yPos);
                        pt3 = pt;
                        points_3.push_back(pt);
                    }
    
                    if(deviceID == "26958"){ // this is our piece
                        pt.set(xPos,yPos);
                        pt4 = pt;
                        points_4.push_back(pt);
                    }
                }
                // both the arguments are ints
                deviceID = m.getArgAsString(0);
                xPos = m.getArgAsInt(1);
                yPos = m.getArgAsInt(2);
            }
            else {
                // unrecognized message: display on the bottom of the screen
                messageBuffer.push_front(m.getAddress() + ": UNRECOGNIZED MESSAGE");
            }
        }
    if (timer) {
        if (points_1.size() > fadeOut) {
            points_1.pop_front();
        }

        if (points_2.size() > fadeOut) {
            points_2.pop_front();
        }

        if (points_3.size() > fadeOut) {
            points_3.pop_front();
        }

        if (points_4.size() > fadeOut) {
            points_4.pop_front();
        }
    }
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    if (drawImage) {
        background_image.draw(0,0, ofGetWidth(), ofGetHeight());
	}
    string buf;
	buf = "listening for osc messages on port" + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
    
    if (players) drawPlayers();
    if (shapes) drawShapes();
    
	// draw mouse state
	buf = ofToString(deviceID, 4) + ": " + ofToString(xPos, 4) +  " " + ofToString(yPos, 4);
	ofDrawBitmapString(buf, 430, 20);

    // read the buffer
	for(int i = 0; i < messageBuffer.size(); i++){
		ofDrawBitmapString(messageBuffer[i], 10, 40 + 15 * i);
	}
}

//--------------------------------------------------------------
void ofApp::drawShapes() {
    ofPushStyle();
        ofColor mixedColor;
        float level = (pt1.x + pt2.x + pt3.x + pt4.x + pt1.y + pt2.y + pt3.y + pt4.y)/8;
        if (level < 200) {
            mixedColor = ofColor::red;
        }
        else if (level < 400 && level > 200) {
            mixedColor = ofColor::orange;
        }
        else if (level < 600 && level > 400) {
            mixedColor = ofColor::yellow;
        }
        else if (level < 600 && level > 400) {
            mixedColor = ofColor::green;
        }
        else {
            mixedColor = ofColor::blue;
        }
        ofSetColor(mixedColor);
        ofBeginShape();
            ofVertex(pt1);
            ofVertex(pt2);
            ofVertex(pt3);
            ofVertex(pt4);
        ofEndShape();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawPlayers() {
    //draw line
    ofPolyline line;
    for (int i= 0; i < points_1.size(); i+= 2){
        line.addVertex(points_1[i]);
    }
    ofPushStyle();
        ofSetColor(color1);
        line.draw();
        line.clear();
    ofPopStyle();
    
    ofPolyline line2;
    for (int i= 0; i < points_2.size(); i+= 2){
        line2.addVertex(points_2[i]);
    }
    ofPushStyle();
        ofSetColor(color2);
        line2.draw();
        line2.clear();
    ofPopStyle();
    
    ofPolyline line3;
    for (int i= 0; i < points_3.size(); i+= 2){
        line3.addVertex(points_3[i]);
    }
    ofPushStyle();
        ofSetColor(color3);
        line3.draw();
        line3.clear();
    ofPopStyle();
    
    ofPolyline line4;
    for (int i= 0; i < points_4.size(); i+= 2){
        line4.addVertex(points_4[i]);
    }
    ofPushStyle();
        ofSetColor(color4);
        line4.draw();
        line4.clear();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        drawImage = !drawImage;
    }
    if (key == 'p') {
        players = !players;
    }
    if (key == 'q') {
        shapes = !shapes;
    }
    if (key == 's'){
        ofSaveScreen("savedScreenshot_"+ofGetTimestampString()+".png");
    }
    if (key == 't') {
        timer = !timer;
    }
    if (key == 'g') {
        ofSaveScreen("savedScreenshot_"+ofGetTimestampString()+".png"); // Save a screenshot with a timestamp when the g key is pressed
        points_1.clear();
        points_2.clear();
        points_3.clear();
        points_4.clear();
    }
    if (key == 'c') {
        points_1.clear();
        points_2.clear();
        points_3.clear();
        points_4.clear();
    }
    if (key == '1') {
        background_image.load("background.jpg");
    }
    if (key == '2') {
        background_image.load("ocean.jpg");
    }
    if (key == '3') {
        background_image.load("battlefield.jpg");
    }
    if (key == '4') {
        background_image.load("crops.jpg");
    }
    if (key == '5') {
        background_image.load("cityStreet.jpg");
    }
    if (key == '6') {
        background_image.load("swimmingPool.jpg");
    }
    if (key == '7') {
        background_image.load("countryRoad.jpg");
    }
}
