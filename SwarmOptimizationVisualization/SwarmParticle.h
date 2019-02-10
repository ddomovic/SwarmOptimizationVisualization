#pragma once

class SwarmParticle {
private:
	float _current_velocity_X;
	float _current_velocity_Y;
	float _current_position_X;
	float _current_position_Y;
	float _personal_best_X;
	float _personal_best_Y;
	float _personal_best_distance;
public:
	SwarmParticle();
	float get_current_velocity_X();
	float get_current_velocity_Y();
	float get_current_position_X();
	float get_current_position_Y();
	float get_personal_best_X();
	float get_personal_best_Y();
	float get_personal_best_distance();
	void set_current_velocity_X(float velocity);
	void set_current_velocity_Y(float velocity);
	void set_current_position_X(float x);
	void set_current_position_Y(float y);
	void set_personal_best_X(float best);
	void set_personal_best_Y(float best);
	void set_personal_best_distance(float best);
	void reset_personal_best();
};