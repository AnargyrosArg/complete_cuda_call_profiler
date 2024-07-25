#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
size_t wrapper_cudnnGetVersion()
{
	size_t retval = cudnnGetVersion();
	return retval;
}