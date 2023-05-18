#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(3);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 90 == 0) {

		this->random_seed = ofRandom(1000);
	}

	ofSeedRandom(this->random_seed);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofColor color;
	for (int i = 0; i < 360; i++) {

		auto location = glm::vec2(ofRandom(0, ofGetWindowWidth()), ofRandom(0, ofGetWindowHeight()));
		location += glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -30, 30), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -30, 30));
		auto scale = ofRandom(3, 8);
		color.setHsb(ofRandom(255), 80, 255);

		ofPushMatrix();
		ofTranslate(location);
		ofRotate(ofRandom(-45, 45));

		ofFill();
		ofSetColor(color);
		ofBeginShape();
		for (int deg = 0; deg < 360; deg++) {

			ofVertex(this->make_point(deg * DEG_TO_RAD) * scale);
		}
		ofEndShape(true);

		color.setSaturation(255);

		ofNoFill();
		ofSetColor(color);
		ofBeginShape();
		for (int deg = 0; deg < 360; deg++) {

			ofVertex(this->make_point(deg * DEG_TO_RAD) * scale);
		}
		ofEndShape(true);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
// Reference by https://twitter.com/shiffman/status/1095764239665512453
glm::vec2 ofApp::make_point(float theta) {

	float x = 16 * (pow(sin(theta), 3));
	float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	return glm::vec2(x, -y);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}