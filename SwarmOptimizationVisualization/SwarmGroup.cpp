#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <math.h>
#include "World.h"
#include "SwarmParticle.h"
#include "SwarmGroup.h"

SwarmGroup::SwarmGroup(World* world) : _group_best_X(1000.0f), _group_best_Y(1000.0f), _world(world) {
	this->_max_velocity_X = 500;
	this->_max_velocity_Y = 500;
	this->_min_velocity_X = -500;
	this->_min_velocity_Y = -500;
}

float SwarmGroup::get_group_best_X() {
	return this->_group_best_X;
}

float SwarmGroup::get_group_best_Y() {
	return this->_group_best_Y;
}

float SwarmGroup::get_group_best_distance() {
	return this->_group_best_distance;
}

float SwarmGroup::get_velocity_modificator() {
	return this->_velocity_modificator;
}

float SwarmGroup::get_learning_factor_1() {
	return this->_learning_factor_1;
}

float SwarmGroup::get_learning_factor_2() {
	return this->_learning_factor_2;
}

const glm::vec4& SwarmGroup::get_group_color() {
	return this->_group_color;
}

const std::vector<class SwarmParticle*>& SwarmGroup::get_particle_DB() {
	return this->_particle_DB;
}

SwarmParticle* SwarmGroup::get_particle_by_index(int i) {
	return this->_particle_DB[i];
}

void SwarmGroup::set_group_best_X(float best) {
	this->_group_best_X = best;
}

void SwarmGroup::set_group_best_Y(float best) {
	this->_group_best_Y = best;
}

void SwarmGroup::set_group_best_distance(float best) {
	this->_group_best_distance = best;
}

void SwarmGroup::set_velocity_modificator(float mod) {
	this->_velocity_modificator = mod;
}

void SwarmGroup::set_learning_factor_1(float l1) {
	this->_learning_factor_1 = l1;
}

void SwarmGroup::set_learning_factor_2(float l2) {
	this->_learning_factor_2 = l2;
}

void SwarmGroup::set_group_color(glm::vec4& color) {
	this->_group_color = color;
}

void SwarmGroup::add_particle(SwarmParticle* new_particle) {
	this->_particle_DB.push_back(new_particle);
}

void SwarmGroup::clear_DB() {
	this->_particle_DB.clear();
}

void SwarmGroup::reset_bests() {
	for (auto p : this->_particle_DB) {
		p->reset_personal_best();
		p->set_personal_best_distance(sqrt(pow(p->get_current_position_X() - this->_world->get_goal_X(), 2) + pow(p->get_current_position_Y() - this->_world->get_goal_Y(), 2)));
	}
	this->_group_best_X = this->_particle_DB[0]->get_current_position_X();
	this->_group_best_Y = this->_particle_DB[0]->get_current_position_Y();
	this->_group_best_distance = this->_particle_DB[0]->get_personal_best_distance();
}

void SwarmGroup::initialize_group(int swarm_size, float velocity_modificator, float learning_factor_1, float learning_factor_2, glm::vec4& color, int screen_width, int screen_height) {
	
	this->clear_DB();
	
	for (int i = 0; i < swarm_size; i++) {
		SwarmParticle* particle = new SwarmParticle();
		particle->set_current_position_X(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / screen_width)));
		particle->set_current_position_Y(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / screen_height)));
		particle->set_personal_best_X(particle->get_current_position_X());
		particle->set_personal_best_Y(particle->get_current_position_Y());
		particle->set_personal_best_distance(sqrt(pow(particle->get_personal_best_X() - this->_world->get_goal_X(), 2) +
			pow(particle->get_personal_best_Y() - this->_world->get_goal_Y(), 2)));
		this->_particle_DB.push_back(particle);
	}
	this->_group_best_X = this->_particle_DB[0]->get_personal_best_X();
	this->_group_best_Y = this->_particle_DB[0]->get_personal_best_Y();
	this->_group_best_distance = sqrt(pow(this->_group_best_X - this->_world->get_goal_X(), 2) +
		pow(this->_group_best_Y - this->_world->get_goal_Y(), 2));
	this->_velocity_modificator = velocity_modificator;
	this->_learning_factor_1 = learning_factor_1;
	this->_learning_factor_2 = learning_factor_2;
	this->_group_color = color;
}

void SwarmGroup::iteration() {
	
	for (auto p : this->_particle_DB) {
		float r1 = ((float)rand() / (RAND_MAX)) + 1;
		float r2 = ((float)rand() / (RAND_MAX)) + 1;
		float new_vel_x = this->_velocity_modificator*p->get_current_velocity_X() +
			r1*this->_learning_factor_1 * (p->get_personal_best_X() - p->get_current_position_X()) +
			r2*this->_learning_factor_2 * (this->_group_best_X - p->get_current_position_X());
		float new_vel_y = this->_velocity_modificator*p->get_current_velocity_Y() +
			r1*this->_learning_factor_1 * (p->get_personal_best_Y() - p->get_current_position_Y()) +
			r2*this->_learning_factor_2 * (this->_group_best_Y - p->get_current_position_Y());
		if (new_vel_x > this->_max_velocity_X) {
			new_vel_x = this->_max_velocity_X;
		}
		if (new_vel_x < this->_min_velocity_X) {
			new_vel_x = this->_min_velocity_X;
		}
		if (new_vel_y > this->_max_velocity_Y) {
			new_vel_y = this->_max_velocity_Y;
		}
		if (new_vel_y < this->_min_velocity_Y) {
			new_vel_y = this->_min_velocity_Y;
		}
		p->set_current_velocity_X(new_vel_x);
		p->set_current_velocity_Y(new_vel_y);
		p->set_current_position_X(p->get_current_position_X() + p->get_current_velocity_X());
		p->set_current_position_Y(p->get_current_position_Y() + p->get_current_velocity_Y());

		/*float distance = sqrt(pow(p->get_current_position_X() - this->_world->get_goal_X(), 2) + 
			pow(p->get_current_position_Y() - this->_world->get_goal_Y(), 2));

		if (distance < this->_group_best_distance) {
			this->_group_best_X = p->get_current_position_X();
			this->_group_best_Y = p->get_current_position_Y();
		}
		if (distance < p->get_personal_best_distance()) {
			p->set_personal_best_X(p->get_current_position_X());
			p->set_personal_best_Y(p->get_current_position_Y());
		}*/
	}
}

void SwarmGroup::update_bests() {
	for (auto p : this->_particle_DB) {
		float distance = sqrt(pow(p->get_current_position_X() - this->_world->get_goal_X(), 2) +
			pow(p->get_current_position_Y() - this->_world->get_goal_Y(), 2));

		if (distance < this->_group_best_distance) {
			this->_group_best_X = p->get_current_position_X();
			this->_group_best_Y = p->get_current_position_Y();
			this->_group_best_distance = distance;
		}
		if (distance < p->get_personal_best_distance()) {
			p->set_personal_best_X(p->get_current_position_X());
			p->set_personal_best_Y(p->get_current_position_Y());
			p->set_personal_best_distance(distance);
		}
	}
}
