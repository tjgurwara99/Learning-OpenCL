#define PROGRAM__h

#include<OpenCL/OpenCL.h>
#include<string>
#include<cassert>
#include<fstream>
#include"cl.hpp"

cl::Program CreateProgram(const char* file){
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	std::vector<cl::Device> devices;

	assert(platforms.size() > 0);
	
	cl::Platform platform = platforms.front();

	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);

	assert(devices.size() > 0);

	cl::Device device = devices.back();

	std::ifstream f(file);
	std::string src((std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()));

	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));

	cl::Context context(device);

	cl::Program program(context, sources);

	cl_int err = program.build();

	if(err == CL_BUILD_ERROR){
		throw(err);
	}
	else{
		return program;
	}
}
