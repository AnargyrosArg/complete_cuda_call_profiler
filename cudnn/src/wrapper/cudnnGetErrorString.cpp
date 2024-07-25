#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
const char * wrapper_cudnnGetErrorString(cudnnStatus_t status)
{
	const char * retval = cudnnGetErrorString(status);
	return retval;
}