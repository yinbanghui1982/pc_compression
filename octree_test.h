#include<CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include "opencl_manager.h"
#include "read_file.h"
#include "octree.h"
#include "range.h"
#include "sort.h"


//kdtree测试
void octree_test()
{
    //获取平台
	cl_uint num_platforms;
	cl_uint status;
	status = clGetPlatformIDs(0,NULL,&num_platforms);

	cl_platform_id platform_id=NULL;
	status = clGetPlatformIDs(1, &platform_id, 0);

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
    const int point_count=10;
    Point2D point2D[point_count]={{-1,-5},{5,-2},{3,-3},{-2,-1},{-4,2},{-3,-4},{1,1},{2,4},{4,3},{-5,5}};
    
	// n: number of points; m: number of leafs
	int n=point_count;
    int m=2;

	//allocate child/parent/split/bounding box indices for m node on GPU


	
    int point_index[point_count],index_x[point_count],index_y[point_count];
    range(point_count,point_index);
    range(point_count,index_x);
    range(point_count,index_y);

    sort(point2D,index_x,0,point_count);
    sort(point2D,index_y,1,point_count);

	int aabb_min_x=index_x[0];
	int aabb_max_x=index_x[point_count-1];
	int aabb_min_y=index_y[0];
	int aabb_max_y=index_y[point_count-1];

	
    int j=1;






}