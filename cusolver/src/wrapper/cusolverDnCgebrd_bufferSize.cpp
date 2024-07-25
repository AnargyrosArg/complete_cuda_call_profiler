#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCgebrd_bufferSize(cusolverDnHandle_t handle, int m, int n, int *Lwork)
{
	cusolverStatus_t retval = cusolverDnCgebrd_bufferSize(handle, m, n, Lwork);
	return retval;
}