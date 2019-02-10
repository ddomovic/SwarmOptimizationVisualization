#include "stdafx.h"
#include "SwarmParticle.h"

SwarmParticle::SwarmParticle() : _current_velocity_X(0.0f), _current_velocity_Y(0.0f), _current_position_X(0.0f), _current_position_Y(0.0f), 
	_personal_best_X(1000.0f), _personal_best_Y(1000.0f) {
}

float SwarmParticle::get_current_velocity_X() {
	return this->_current_velocity_X;
}

float SwarmParticle::get_current_velocity_Y() {
	return this->_current_velocity_Y;
}

float SwarmParticle::get_current_position_X() {
	return this->_current_position_X;
}

float SwarmParticle::get_current_position_Y() {
	return this->_current_position_Y;
}

float SwarmParticle::get_personal_best_X() {
	return this->_personal_best_X;
}

float SwarmParticle::get_personal_best_Y() {
	return this->_personal_best_Y;
}

float SwarmParticle::get_personal_best_distance() {
	return this->_personal_best_distance;
}

void SwarmParticle::set_current_velocity_X(float velocity) {
	this->_current_velocity_X = velocity;
}

void SwarmParticle::set_current_velocity_Y(float velocity) {
	this->_current_velocity_Y = velocity;
}

void SwarmParticle::set_current_position_X(float x) {
	this->_current_position_X = x;
}

void SwarmParticle::set_current_position_Y(float y) {
	this->_current_position_Y = y;
}

void SwarmParticle::set_personal_best_X(float best) {
	this->_personal_best_X = best;
}

void SwarmParticle::set_personal_best_Y(float best) {
	this->_personal_best_Y = best;
}

void SwarmParticle::set_personal_best_distance(float best) {
	this->_personal_best_distance = best;
}

void SwarmParticle::reset_personal_best() {
	this->set_personal_best_X(this->_current_position_X);
	this->set_personal_best_Y(this->_current_position_Y);
}
