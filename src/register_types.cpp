#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "register_types.h"
#include "Main.h"
#include "Mob.h"
#include "Player.h"
#include "ScoreLabel.h"

using namespace godot;

void initialize_libgdextension_types(ModuleInitializationLevel p_level)
{
	if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
	ClassDB::register_class<Main>();
	ClassDB::register_class<Mob>();
	ClassDB::register_class<Player>();
	ClassDB::register_class<ScoreLabel>();
}

void uninitialize_libgdextension_types(ModuleInitializationLevel p_level)
{
	if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
}

extern "C" {
// Initialization
GDExtensionBool GDE_EXPORT libgdextension_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library,
                                               GDExtensionInitialization*         r_initialization)
{
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
	init_obj.register_initializer(initialize_libgdextension_types);
	init_obj.register_terminator(uninitialize_libgdextension_types);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
