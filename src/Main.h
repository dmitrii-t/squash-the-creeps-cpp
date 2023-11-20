#pragma once
#ifndef SQUASH_THE_CREEPS_MAIN_H
#define SQUASH_THE_CREEPS_MAIN_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/control.hpp"

namespace godot
{
	/*
	 * The Main scene class
	 */
	class Main : public Node
	{
		GDCLASS(Main, Node)

		void set_mob_scene(Ref<PackedScene> p_scene);
		Ref<PackedScene> get_mob_scene();

		void _on_mob_timer_timeout();	

		void _ready() override;
		void _unhandled_input(const Ref<InputEvent> &event) override;

		
		Main();
		~Main() override;

	protected:
		static void _bind_methods();
		Ref<PackedScene> mob_scene;

		// TODO This should eb converted to Ref<Control>
		Control *retry = nullptr;
	};
}
#endif // !MAIN_H
