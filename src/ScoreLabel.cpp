#include "ScoreLabel.h"

using namespace godot;

void ScoreLabel::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("_on_Mob_squashed"), &ScoreLabel::_on_Mob_squashed);
}

void ScoreLabel::_on_Mob_squashed()
{
	this->score += 1;
	this->set_text(vformat("Score: %s", this->score));
}

ScoreLabel::ScoreLabel()
= default;
