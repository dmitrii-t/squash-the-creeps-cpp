#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/animation_player.hpp>

#include "math_defs.h"
#include "Mob.h"

#include "godot_cpp/variant/utility_functions.hpp"

using namespace godot;

void Mob::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("_on_visible_on_screen_notifier_screen_exited"), &Mob::_on_visible_on_screen_notifier_screen_exited);
	
	ADD_SIGNAL(MethodInfo("squashed"));
}

void Mob::initialize(Vector3 start_position, Vector3 player_position)
{
	this->look_at_from_position(start_position, player_position, Vector_UP);
	this->rotate_y(rng->randf_range(-Math_PI / 4, Math_PI / 4));

	const double random_speed = rng->randf_range(min_speed, max_speed);
	// We calculate a forward velocity first, which represents the speed.
	Vector3 velocity = Vector_FORWARD * random_speed;
	// We then rotate the vector based on the mob's Y rotation to move in the direction it's looking.
	velocity = velocity.rotated(Vector_UP, get_rotation().y);
	this->set_velocity(velocity);

	AnimationPlayer *animation_player = get_node<AnimationPlayer>("AnimationPlayer");
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
