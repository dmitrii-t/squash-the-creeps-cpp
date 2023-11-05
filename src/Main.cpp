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

Main::Main()
{
}

Main::~Main()
{
	
}
