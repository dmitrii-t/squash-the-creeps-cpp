#include "Main.h"

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>

#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/engine.hpp"

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
}

void Main::_unhandled_input(const Ref<InputEvent> &event)
{
	UtilityFunctions::print("Main::_unhandled_input");
}

void Main::_on_mob_timer_timeout()
{
	UtilityFunctions::print("Main::_on_mob_timer_timeout");
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
{
}

Main::~Main()
{
	
}
