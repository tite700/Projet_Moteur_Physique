#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofConstants.h"

#include "../Vector.h"
#include "../Particule.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void ofApp::posInitChanged(glm::vec2& newValue);

		ofxFloatSlider rayon;
		ofxFloatSlider masse;
		ofxVec2Slider pos_init;
		ofxToggle startButton;


		ofxPanel gui;

		Particule particule = Particule(Vector::zeros(), 0);	

		
};
