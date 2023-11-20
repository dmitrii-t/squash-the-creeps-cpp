#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/engine.hpp"
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/path_follow3d.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/variant/callable.hpp>

#include "Main.h"
#include "Mob.h"
#include "ScoreLabel.h"

using namespace godot;

void Main::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("_on_mob_timer_timeout"), &Main::_on_mob_timer_timeout);

	// Property mob_scene
	ClassDB::bind_method(D_METHOD("set_mob_scene", "shortcut"), &Main::set_mob_scene);
	ClassDB::bind_method(D_METHOD("get_mob_scene"), &Main::get_mob_scene);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mob_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_mob_scene", "get_mob_scene");
}

void Main::_ready()
{
	UtilityFunctions::print("Main::_ready");

	NodePath np = NodePath("UserInterface/Retry");
	retry = get_node<Control>(np);
	retry->hide();
}

void Main::_unhandled_input(const Ref<InputEvent> &event)
{
	UtilityFunctions::print("Main::_unhandled_input");

	if(event->is_action_pressed("ui_accept") && retry->is_visible())
	{
		get_tree()->reload_current_scene();
	}
}

void Main::_on_mob_timer_timeout()
{
	UtilityFunctions::print("Main::_on_mob_timer_timeout");

	Mob *mob = nullptr;

	// Create a new instance of the Mob scene
	Ref<PackedScene> mob_scene = ResourceLoader::get_singleton()->load("res://Mob.tscn");
	if(mob_scene.is_valid())
	{
		// instantiate mob_scene and cast it to a Mob
		mob = Object::cast_to<Mob>(mob_scene->instantiate());
	}

	// Choose a random location on the SpawnPath
	PathFollow3D *mob_spawn_location = get_node<PathFollow3D>("SpawnPath/SpawnLocation");
	mob_spawn_location->set_progress_ratio(UtilityFunctions::randf());

	CharacterBody3D *player = get_node<CharacterBody3D>("Player");

	// Communicate the spawn location and the player's location to the mob.
	Vector3 player_position = player->get_position();
	mob->initialize(mob_spawn_location->get_position(), player_position);

	add_child(mob);

	ScoreLabel *score_label = get_node<ScoreLabel>("UserInterface/ScoreLabel");
	// mob->connect("squashed", score_label, &ScoreLabel::_on_Mob_squashed);
	mob->connect("squashed", Callable(score_label, "_on_Mob_squashed"));
}

void Main::set_mob_scene(Ref<PackedScene> p_scene)
{
	mob_scene = p_scene;
}

Ref<PackedScene> Main::get_mob_scene()
{
	return mob_scene;
}

Main::Main()
= default;

Main::~Main()
{
	delete retry;
}
