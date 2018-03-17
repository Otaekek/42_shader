#pragma once

#include <cstdint>
#include <transform.class.hpp>
#include "../memory_allocator/stackAllocator.class.hpp"
#include "../../assimp/include/assimp/scene.h"
#include "../file_loader/fileLoader.class.hpp"
#include "meshData.hpp"
#include <texture_builtin.class.hpp>
#include <FreeImage.h>
#include <glm.hpp>
#include <cstdlib>
#include <jojishi.hpp>
#include <string>
#include <mutex>
#include <fcntl.h>

#include <cstdlib>
#include <math.h> 
#include <cstring>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdint.h> 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>

enum SHADER_ID {
	NONE = 0
};

class shader {

public :
	shader();
	~shader();

	void		use() { glUseProgram(program); }
	void		recompile();
	bool		check_date();
	uint32_t	load_shader(std::string path, int type);
	void		add(std::string path, int p_type);

	bool		check_dirty() { if (dirty) return dirty; return check_date();}
	void		update() { if (check_dirty()) recompile(); }
	void		init() {shadersCount = 0; dirty = false; }

	uint32_t		shaders[6];
	std::string		fileName[6];
	struct stat		shadersStats[6];
	uint32_t		shadersCount;
	uint32_t		program;
	uint32_t		type[6];

	bool			dirty;

	std::string 	readfile(std::string path);
};

class shaderSystem {

public:

	shaderSystem() {shadersCount = 0;}
	~shaderSystem() {} ;

	shader		shaders[4096];
	uint32_t	shadersTypeToId[4096];
	uint32_t	shadersCount;

	void 	create(SHADER_ID id) {shaders[shadersCount].init(); shadersTypeToId[id] = shadersCount++;} 

	void	add(SHADER_ID id, std::string path, int type) { shaders[shadersTypeToId[id]].add(path, type); }

	void	update() { for (int i = 0; i < shadersCount; ++i ) shaders[i].update(); }

	shader		get_shader(SHADER_ID id) { return shaders[shadersTypeToId[id]]; }
	uint32_t	get_program(SHADER_ID id) {return shaders[shadersTypeToId[id]].program; }
};

