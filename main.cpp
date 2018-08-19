#include<iostream>
#include"program.h"
#include<vector>


int main(){
	cl::Program program = CreateProgram("vadd.cl");

	cl::Context context = program.getInfo<CL_PROGRAM_CONTEXT>();
	std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();

	cl::Device  device = devices.back();

	std::vector<double> a(100, 4);
	std::vector<double> b(100, 5);

	std::vector<double> c(100);

	cl::Buffer a_buffer(context, begin(a), end(a), true);
	cl::Buffer b_buffer(context, begin(b), end(b), true);

	cl::Buffer c_buffer(context, CL_MEM_WRITE_ONLY, sizeof(double) * c.size());

	cl::make_kernel<cl::Buffer, cl::Buffer, cl::Buffer> vadd(program, "vadd");

	cl::CommandQueue queue(context, device);

	vadd(
			cl::EnqueueArgs(queue, cl::NDRange(100)),
			a_buffer,
			b_buffer,
			c_buffer);

	queue.finish();

	cl::copy(queue, c_buffer, begin(c), end(c));
	
	
	for(int i=0; i<c.size(); ++i){
		std::cout<<c[i]<<std::endl;
	}
	return 0;
}


