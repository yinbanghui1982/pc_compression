#include<CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include "read_file.h"
#pragma once


class OpenclManager
{

    private:
        cl_uint num_platforms;                              
        cl_platform_id platform_id=NULL;        
        cl_uint num_devices;
        cl_device_id device_id;
        cl_context context;
        cl_command_queue queue ;

    public:
        OpenclManager() { }

        void GetPlatForms()
        {
            cl_uint status;
            status = clGetPlatformIDs(0,NULL,&num_platforms);            
            status = clGetPlatformIDs(1, &platform_id, 0);
        }

        void GetDevices()
        {            
            clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 0, NULL, &num_devices);            
            clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);
        }

        void CreateContext()
        {
            context = clCreateContext(0, 1, &device_id, 0, 0, 0);
        }

        void CreateCommandQueue()
        {
            queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, 0);
        }




};