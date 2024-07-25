#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroy(cudnnHandle_t handle)
{
	cudnnStatus_t retval = cudnnDestroy(handle);
	return retval;
}