#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetStream(cudnnHandle_t handle, cudaStream_t streamId)
{
	cudnnStatus_t retval = cudnnSetStream(handle, streamId);
	return retval;
}