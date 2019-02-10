#pragma once

#include <vector>

class World {
private:
	float _goal_position_X;
	float _goal_position_Y;
	std::vector<class SwarmGroup*> _groups;
public:
	World();
	float get_goal_X();
	float get_goal_Y();
	std::vector<class SwarmGroup*>& get_groups();
	void set_goal_X(float x);
	void set_goal_Y(float y);
	void set_groups(std::vector<class SwarmGroup*>& groups);
	void reset_groups();
	static void draw_circle(float radius, float position_X, float position_Y);
	void draw();
	void run();
};