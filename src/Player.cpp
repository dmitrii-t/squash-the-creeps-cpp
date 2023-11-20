#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/math.hpp>

#include "Player.h"
#include "Mob.h"
#include "Math.h"

using namespace godot;

void Player::_bind_methods()
{
	
}

void Player::_physics_process(double delta)
{
	Vector3 direction = Vector_ZERO;
	if(Input::get_singleton()->is_action_pressed("move_right"))
	{
		direction += Vector3(1, 0, 0);
	}
	if(Input::get_singleton()->is_action_pressed("move_left"))
	{
		direction += Vector3(-1, 0, 0);
	}
	if(Input::get_singleton()->is_action_pressed("move_back"))
	{
		direction += Vector3(0, 0, 1);
	}
	if(Input::get_singleton()->is_action_pressed("move_forward"))
	{
		direction += Vector3(0, 0, -1);
	}

	Node3D *         pivot = get_node<Node3D>("Pivot");
	AnimationPlayer *animation_player = get_node<AnimationPlayer>("AnimationPlayer");

	if(direction != Vector_ZERO)
	{
		// In the lines below, we turn the character when moving and make the animation play fast
		direction = direction.normalized();

		// Setting the basis property will affect the rotation of the node.
		pivot->set_basis(Basis::looking_at(direction));
		animation_player->set_speed_scale(4);
	}
	else
	{
		animation_player->set_speed_scale(1);
	}

	Vector3 velocity = this->get_velocity();
	velocity.x = direction.x * speed;
	velocity.z = direction.z * speed;

	// Jumping.
	if(this->is_on_floor() && Input::get_singleton()->is_action_pressed("jump"))
	{
		velocity.y += jump_impulse;
	}

	// Falling.
	if(!this->is_on_floor())
	{
		velocity.y -= fall_acceleration * delta;
	}

	// Apply velocity and move.
	this->set_velocity(velocity);
	this->move_and_slide();

	// Here, we check if we landed on top of a mob and if so, we kill it and bounce.
	// With move_and_slide(), Godot makes the body move sometimes multiple times in a row to
	// smooth out the character's motion. So we have to loop over all collisions that may have
	// happened.
	// If there are no "slides" this frame, the loop below won't run.
	for(int i = 0, count = this->get_slide_collision_count(); i < count; i++)
	{
		Ref<KinematicCollision3D> collision = this->get_slide_collision(i);
		Node                     *collider = Object::cast_to<Node>(collision->get_collider());
		if(collider->is_in_group("mob"))
		{
			Mob *mob = Object::cast_to<Mob>(collider);
			if(Vector_UP.dot(collision->get_normal()) > 0.1)
			{
				mob->squash();

				// Bouncing.
				velocity.y = -bounce_impulse;
				break;
			}
		}
	}

	// This makes the character follow a nice arc when jumping
	Vector3 rotation = pivot->get_rotation();
	rotation.x = Math_PI / 6 * velocity.y / jump_impulse;
	pivot->set_rotation(rotation);
}

void Player::die()
{
	this->emit_signal("hit");
	this->queue_free();
}

void Player::_onModDetector_body_entered()
{
	this->die();
}
