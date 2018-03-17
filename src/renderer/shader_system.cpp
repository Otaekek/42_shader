#include "shader_system.hpp"

#ifdef  __APPLE__
# define FILE_AGE(F)(F.st_mtimespec.tv_sec)
#else
# define FILE_AGE(F)(F.st_mtim.tv_sec)
#endif


std::string 		shader::readfile(std::string path)
{
	std::string line;
	std::string file;
	std::ifstream myfile(path);
	if (myfile.is_open())
	{
		while ( getline (myfile, line) )
			file += line + '\n';
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file: " << path << std::endl;
		exit(0);
	}
	return file;
}

bool shader::check_date() {

	struct stat 		libstat;
	int					statret;

	for (int i = 0; i < shadersCount; ++i) {
		statret = stat(fileName[i].c_str(), &libstat);
		if (FILE_AGE(libstat) < FILE_AGE(shadersStats[i])) {
			shadersStats[i] = libstat;
			dirty = true;
		}
	}
	return dirty;
}

void shader::recompile() {
	program = glCreateProgram();
	for (int i = 0; i < shadersCount; ++i) {
		glAttachShader(program, load_shader(fileName[i], type[i]));
	}
	glLinkProgram(program);
}

void shader::add(std::string path, int p_type) {

	struct stat 		libstat;

	dirty = true;
	shaders[shadersCount] = load_shader(path, p_type);
	stat(path.c_str(), &libstat);
	fileName[shadersCount] = path;
	shadersStats[shadersCount] = libstat;
	type[shadersCount] = p_type;
	recompile();
}

uint32_t shader::load_shader(std::string path, int type)
{
	GLchar			*code;
	GLuint			shaderObject;
	GLint			length;
	GLint			compiled;
	char			log[4096];
	GLint			blen, slen;
	std::string 	file;

	printf("Compiling shader ... %s\n", path.c_str());
	code = (GLchar*)malloc(4096);
	file = fileLoader::readfile(path);
	memcpy(code, file.c_str(), file.length() + 1);
	shaderObject = glCreateShader(type);
	length = strlen(code);
	glShaderSource(shaderObject, 1, (const GLchar **)&(code), &length);
	glCompileShader(shaderObject);
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH , &blen);
		printf("%d\n", compiled);
		glGetShaderInfoLog(shaderObject, blen, &slen, log);
		printf("VertexShader compilation: %s\n", log);
		exit(0);
	}
	printf("Shader compilation sucess %s\n", path.c_str());
	free(code);
	return (shaderObject);
}
