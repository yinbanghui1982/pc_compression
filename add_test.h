#include<CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include "opencl_manager.h"
#include "read_file.h"

void add_test()
{
	//获取平台
	cl_uint num_platforms;
	cl_uint status;
	status = clGetPlatformIDs(0,NULL,&num_platforms);

	cl_platform_id platform_id=NULL;
    cl_uint platform_num2=0;
	status = clGetPlatformIDs(1, &platform_id, &platform_num2);

	//获取设备
	cl_uint num_devices;
	clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 0, NULL, &num_devices);
	cl_device_id device_id;
	clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);


	//创建上下文
	cl_context context = clCreateContext(0, 1, &device_id, 0, 0, 0);

	//创建命令队列
	cl_command_queue queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, 0);

	//创建内存对象
	cl_uint a_array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	cl_uint b_array[] = { 3, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	cl_uint c_array[sizeof(a_array) / sizeof(a_array[0])] = { 0 };
	cl_mem clAArrBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(a_array), a_array, 0);
	cl_mem clBArrBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(b_array), b_array, 0);
	cl_mem clCArrBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(c_array), c_array, 0);
	

	//创建程序
	size_t len = 0;
	char* code = readFile("kernel.cl", &len);
	if (code == 0)
	{
		printf("Can not open file\n");
	}

	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&code, &len, 0);
	delete code, code = 0;
	status = clBuildProgram(program, 1, &device_id, 0, 0, 0);
	if (status != CL_SUCCESS)
	{
		printf("Build failed: %d\n", status);
		char tbuf[1024];
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 1024, tbuf, NULL);
		printf("\n%s\n", tbuf);
	}

	//创建Kernel	
	cl_kernel kernel = clCreateKernel(program, "Add", 0);

	//设置Kernel参数
	cl_uint sizeOfArr = sizeof(a_array) / sizeof(a_array[0]);
	clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&clAArrBuffer);	
	clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&clBArrBuffer);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&clCArrBuffer);	
	//clSetKernelArg(kernel, 3, sizeof(cl_uint), (void*)&sizeOfArr);	

	//Kernel入队执行
	cl_uint work_dim = 1;
	size_t global_work_size = sizeOfArr;	//维数
	clEnqueueNDRangeKernel(queue, kernel, work_dim, 0, &global_work_size, 0, 0, 0, 0);

	//读取结果
	clEnqueueReadBuffer(queue, clCArrBuffer, CL_TRUE, 0, sizeof(c_array), c_array, 0, 0, 0);

	//释放内存
	clReleaseMemObject(clAArrBuffer);
	clReleaseMemObject(clBArrBuffer);
	clReleaseMemObject(clCArrBuffer);
	

	//释放Kernel
	clReleaseKernel(kernel);

	//释放命令队列
	clReleaseCommandQueue(queue);

	//释放上下文
	clReleaseContext(context);

	//主机处理
	for (int i = 0; i < sizeof(c_array) / sizeof(c_array[0]); ++i)
		printf("%d\n", c_array[i]);

	// system("pause");


}
