#pragma once
#ifndef SQUASH_THE_CREEPS_MAIN_H
#define SQUASH_THE_CREEPS_MAIN_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/classes/timer.hpp"

#include "ScoreLabel.h"

namespace godot
{
    /*
     * The Main scene class
     */
    class Main : public Node
    {
        GDCLASS(Main, Node)

    public:    
        void set_mob_scene(Ref<PackedScene> p_scene);
        Ref<PackedScene> get_mob_scene();

        void _on_mob_timer_timeout();
        void _on_player_hit();

        void _ready() override;
        void _unhandled_input(const Ref<InputEvent> &event) override;


        Main();

    protected:
        static void _bind_methods();
        Ref<PackedScene> mob_scene;

        Control *retry = nullptr;
        ScoreLabel *score_label = nullptr;
        Timer *mob_timer = nullptr;
    };
}
#endif // !MAIN_H
