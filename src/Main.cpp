#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/engine.hpp"
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/path_follow3d.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/variant/callable.hpp>
#include "godot_cpp/classes/timer.hpp"

#include "Main.h"
#include "Mob.h"
#include "ScoreLabel.h"

using namespace godot;

void Main::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("_on_mob_timer_timeout"), &Main::_on_mob_timer_timeout);
    ClassDB::bind_method(D_METHOD("_on_player_hit"), &Main::_on_player_hit);


    // Property mob_scene
    ClassDB::bind_method(D_METHOD("set_mob_scene", "shortcut"), &Main::set_mob_scene);
    ClassDB::bind_method(D_METHOD("get_mob_scene"), &Main::get_mob_scene);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mob_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"),
                 "set_mob_scene", "get_mob_scene");
}

void Main::_ready()
{
    UtilityFunctions::print("Main scene _ready()");

    score_label = get_node<ScoreLabel>("UserInterface/ScoreLabel");

    retry = get_node<Control>("UserInterface/Retry");
    retry->hide();

    mob_timer = get_node<Timer>("MobTimer");
}

void Main::_unhandled_input(const Ref<InputEvent> &event)
{
    if (event->is_action_pressed("ui_accept") && retry->is_visible())
    {
        UtilityFunctions::print("Reloading the scene");

        auto error = get_tree()->reload_current_scene();
        if (error != OK)
        {
            UtilityFunctions::print("Error reloading scene: ", error);
        }
    }
}

void Main::_on_mob_timer_timeout()
{
    Mob *mob = nullptr;

    // Create a new instance of the Mob scene
    if (mob_scene.is_valid())
    {
        mob = Object::cast_to<Mob>(mob_scene->instantiate());    
    }
    
    // Choose a random location on the SpawnPath
    PathFollow3D *mob_spawn_location = get_node<PathFollow3D>("SpawnPath/SpawnLocation");
    mob_spawn_location->set_progress_ratio(UtilityFunctions::randf());

    const CharacterBody3D *player = get_node<CharacterBody3D>("Player");

    // Communicate the spawn location and the player's location to the mob.
    const Vector3 player_position = player->get_position();
    mob->initialize(mob_spawn_location->get_position(), player_position);

    add_child(mob);

    // Connect the mob squashed method to the score label
    mob->connect("squashed", Callable(score_label, "_on_Mob_squashed"));
}

void Main::_on_player_hit()
{
    mob_timer->stop();
    retry->show();
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
