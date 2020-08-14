__kernel void Multiply2(__global uint* indata, __global uint* outdata)
{
	uint idx = get_global_id(0);
	outdata[idx] = indata[idx] * 2;
}

__kernel void Multiply3(__global uint* indata, __global uint* outdata)
{
	uint idx = get_global_id(0);
	outdata[idx] = indata[idx] * 3;
}


__kernel void Add(__global uint* A,__global uint* B, __global uint* C)
{
	uint idx = get_global_id(0);
	C[idx] = A[idx]+B[idx];
}