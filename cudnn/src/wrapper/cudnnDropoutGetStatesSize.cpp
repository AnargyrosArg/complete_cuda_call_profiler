#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDropoutGetStatesSize(cudnnHandle_t handle, size_t *sizeInBytes)
{
	cudnnStatus_t retval = cudnnDropoutGetStatesSize(handle, sizeInBytes);
	return retval;
}