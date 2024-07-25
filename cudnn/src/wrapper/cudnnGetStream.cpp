#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetStream(cudnnHandle_t handle, cudaStream_t *streamId)
{
	cudnnStatus_t retval = cudnnGetStream(handle, streamId);
	return retval;
}