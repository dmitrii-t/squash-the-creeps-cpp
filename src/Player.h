#pragma once
#ifndef SQUASH_THE_CREEPS_PLAYER_H
#define SQUASH_THE_CREEPS_PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>

namespace godot
{
	class Player : public CharacterBody3D
	{
		GDCLASS(Player, CharacterBody3D);
		
		void _physics_process(double delta) override;
		void _onModDetector_body_entered();
		void die();
		
		Player();
		
	protected:
		static void _bind_methods();

		double speed = 14;
		double jump_impulse = 20;
		double bounce_impulse = 16;
		double fall_acceleration = 75;
		
	};
}

#endif
