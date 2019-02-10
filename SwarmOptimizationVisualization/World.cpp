#include "stdafx.h"
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "SwarmParticle.h"
#include "SwarmGroup.h"
#include "World.h"

World::World() : _goal_position_X(0.0f), _goal_position_Y(0.0f) {
}

float World::get_goal_X() {
	return this->_goal_position_X;
}

float World::get_goal_Y() {
	return this->_goal_position_Y;
}

std::vector<class SwarmGroup*>& World::get_groups() {
	return this->_groups;
}

void World::set_goal_X(float x) {
	this->_goal_position_X = x;
}

void World::set_goal_Y(float y) {
	this->_goal_position_Y = y;
}

void World::set_groups(std::vector<class SwarmGroup*>& groups) {
	this->_groups = groups;
}

void World::reset_groups() {
	for (auto g : this->_groups) {
		g->reset_bests();
	}
}

void World::draw_circle(float radius, float position_X, float position_Y) {
	float x1, y1, x2, y2;
	float angle;
	
	x1 = position_X, y1 = position_Y;
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (angle = 1.0f; angle<361.0f; angle += 0.2) {
		x2 = x1 + sin(angle)*radius;
		y2 = y1 + cos(angle)*radius;
		glVertex2f(x2, y2);
	}

	glEnd();
}

void World::draw() {

	draw_circle(15.0f, this->_goal_position_X, this->_goal_position_Y);

	for (auto g : this->_groups) {
		glm::vec4 c = g->get_group_color();
		glColor4f(c.x, c.y, c.z, c.w);
		glBegin(GL_POINTS);
		for (auto p : g->get_particle_DB()) {
			glVertex2f(p->get_current_position_X(), p->get_current_position_Y());
		}
		glEnd();
	}
}

void World::run() {

	for (auto g : this->_groups) {
		g->iteration();
		g->update_bests();
	}
}
