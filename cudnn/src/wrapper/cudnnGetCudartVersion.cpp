#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
size_t wrapper_cudnnGetCudartVersion()
{
	size_t retval = cudnnGetCudartVersion();
	return retval;
}