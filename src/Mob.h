#pragma once
#ifndef SQUASH_THE_CREEPS_MOB_H
#define SQUASH_THE_CREEPS_MOB_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

namespace godot
{
	class Mob : public CharacterBody3D
	{
		GDCLASS(Mob, CharacterBody3D)
		
	public:
		void initialize(Vector3 start_position, Vector3 player_position);
		
		void squash();

		void _on_visible_on_screen_notifier_screen_exited();
		void _physics_process(double delta) override;
		
		void set_max_speed(double max_speed);
		double get_max_speed();
		
		void set_min_speed(double min_speed);
		double get_min_speed();

		Mob();
		~Mob();
		
	protected:
		static void _bind_methods();
	
	private:
		RandomNumberGenerator *rng;
		double max_speed;
		double min_speed;
		
	};
}


#endif // !MOB_H