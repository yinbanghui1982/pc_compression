#include<CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include "opencl_manager.h"
#include "add_test.h"
#include "kdtree_test.h"


int main()
{
	// add_test();
	kdtree_test();


	// OpenclManager* openclManeger=new OpenclManager();
	// openclManeger->GetPlatForms();

    return 0;
}