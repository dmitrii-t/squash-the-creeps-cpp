#pragma once
#ifndef SQUASH_THE_CREEPS_SCORELABEL_H
#define SQUASH_THE_CREEPS_SCORELABEL_H

#include <godot_cpp/classes/label.hpp>

namespace godot
{
	class ScoreLabel : public Label
	{
		GDCLASS(ScoreLabel, Label)

		void _on_Mob_squashed();
		
		ScoreLabel();

	protected:
		static void _bind_methods();

	private:
		double score;
	};
}

#endif
