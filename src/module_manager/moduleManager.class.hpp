#pragma once

#include <Jarray.hpp>

class moduleManager {

	static void init();
	static void update();
	static void release();

	static void add_module(AModule *module);

	static Jarray<AModule> modules;
}
