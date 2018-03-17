#pragma once

#define MAX_MODULES 256

#include <jojishi.hpp>
#include <Jarray.hpp>


class moduleManager {

	static void init();
	static void update();
	static void release();

	static void add_module(AModule *module);

	static JConstantArray<AModule, MAX_MODULES> modules;
}
