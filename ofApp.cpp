#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofFill();

	auto radius = 300;
	auto noise_step = 0.001;
	vector<glm::vec3> vertices;
	for (auto deg = 0; deg < 360; deg += 1) {

		auto noise_location = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);
		auto noise_seed_x = noise_location.x * 0.001;
		auto noise_seed_y = noise_location.y * 0.001;
		auto noise_seed_z = noise_location.z;

		auto angle_x = ofMap(ofNoise(noise_seed_x, ofGetFrameNum() * noise_step), 0, 1, -PI * 2, PI * 2);
		auto angle_y = ofMap(ofNoise(noise_seed_y, ofGetFrameNum() * noise_step), 0, 1, -PI * 2, PI * 2);
		auto angle_z = ofMap(ofNoise(noise_seed_z, ofGetFrameNum() * noise_step), 0, 1, -PI * 2, PI * 2);

		auto location = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);
		auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
		auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
		auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));
		location = glm::vec4(location, 0) * rotation_z * rotation_y * rotation_x;

		ofDrawSphere(location, 3);
		vertices.push_back(location);
	}

	ofNoFill();
	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}