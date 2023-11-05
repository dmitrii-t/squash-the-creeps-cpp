﻿#pragma once
#ifndef MAIN_H
#define MAIN_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/input_event.hpp>

#include "godot_cpp/classes/packed_scene.hpp"

namespace godot
{
	/*
	 * The Main scene class
	 */
	class Main : public Node
	{
		GDCLASS(Main, Node)

	public:
		void _on_mob_timer_timeout();	

		void _ready() override;
		void _unhandled_input(const Ref<InputEvent> &event) override;

		
		Main();
		~Main() override;

	protected:
		static void _bind_methods();
	};
}
#endif // !MAIN_H