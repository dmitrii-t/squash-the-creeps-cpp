﻿#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/variant/basis.hpp>
#include <godot_cpp/classes/animation_player.hpp>


#include "Mob.h"

using namespace godot;

const auto FORWARD = Vector3(1, 0, 0);
const auto UP = Vector3(0, 1, 0);

void Mob::_bind_methods()
{
	ADD_SIGNAL(MethodInfo("squashed"));
}

void Mob::initialize(Vector3 start_position, Vector3 player_position)
{
	this->look_at_from_position(start_position, player_position, UP);
	rotate_y(rng->randf_range(-Math_PI / 4, Math_PI / 4));

	double random_speed = rng->randf_range(min_speed, max_speed);
	// We calculate a forward velocity first, which represents the speed.
	auto velocity = FORWARD * random_speed;
	// We then rotate the vector based on the mob's Y rotation to move in the direction it's looking.
	velocity = velocity.rotated(UP, get_rotation().y);
	set_velocity(velocity);

	NodePath np = NodePath("AnimationPlayer");
	auto     animation_player = get_node<AnimationPlayer>(np);
	animation_player->set_speed_scale(random_speed / min_speed);
}


void Mob::squash()
{
	emit_signal("squashed");
	queue_free();
}


void Mob::_physics_process(double delta)
{
	move_and_slide();
}

void Mob::_on_visible_on_screen_notifier_screen_exited()
{
	queue_free();
}

Mob::Mob()
{
	rng = new RandomNumberGenerator;
}

Mob::~Mob()
{
	delete rng;
}
