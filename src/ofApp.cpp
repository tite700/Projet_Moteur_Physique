#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();

	gui.add(rayon.setup("Radius", 15, 5, 50));
	gui.add(masse.setup("Masse", 5, 1, 100));
	gui.add(pos_init.setup("Initial position", { 30, 170 }, { 30, 170 }, { ofGetWidth()-20, ofGetHeight()-20}));
	gui.add(startButton.setup("Click or Spacebar",false));

	particule.setVelocite(Vector(1, 1, 0));
	particule.setAcceleration(Vector(5, 5, 0));
	

}


//--------------------------------------------------------------
void ofApp::update(){
	
	if (!startButton) {
		particule.setPos(Vector(pos_init->x, pos_init->y, 0));
	}

	particule.setRadius(rayon);
	particule.setMasse(masse);

	particule.update();

	if (startButton) {
		particule.start();
	}

	if (particule.getPos().x < 0 || particule.getPos().x > ofGetWidth() || particule.getPos().y < 0 || particule.getPos().y > ofGetHeight()) {
		particule.setHasStarted(false);
		startButton = false;
		particule.setPos(Vector(pos_init->x, pos_init->y, 0));
	}


}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackgroundGradient(ofColor::black, ofColor::darkGray);

	particule.draw();
	//ofDrawSphere(center->x,center->y, radius);
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == ' ') {
		startButton = !startButton;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
