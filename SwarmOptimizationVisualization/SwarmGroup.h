#pragma once

#include <vector>
#include <glm/glm.hpp>

class SwarmGroup {
private:
	float _group_best_X;
	float _group_best_Y;
	float _group_best_distance;
	float _velocity_modificator;
	float _learning_factor_1;
	float _learning_factor_2;
	float _min_velocity_X;
	float _min_velocity_Y;
	float _max_velocity_X;
	float _max_velocity_Y;
	class World* _world;
	glm::vec4 _group_color;
	std::vector<class SwarmParticle*> _particle_DB;
public:
	SwarmGroup(class World* world);
	float get_group_best_X();
	float get_group_best_Y();
	float get_group_best_distance();
	float get_velocity_modificator();
	float get_learning_factor_1();
	float get_learning_factor_2();
	const glm::vec4& get_group_color();
	const std::vector<class SwarmParticle*>& get_particle_DB();
	class SwarmParticle* get_particle_by_index(int i);
	void set_group_best_X(float best);
	void set_group_best_Y(float best);
	void set_group_best_distance(float best);
	void set_velocity_modificator(float mod);
	void set_learning_factor_1(float l1);
	void set_learning_factor_2(float l2);
	void set_group_color(glm::vec4& color);
	void add_particle(class SwarmParticle* new_particle);
	void clear_DB();
	void reset_bests();
	void initialize_group(int swarm_size, float velocity_modificator, float learning_factor_1, float learning_factor_2, glm::vec4& color, int screen_width, int screen_height);
	void iteration();
	void update_bests();
};