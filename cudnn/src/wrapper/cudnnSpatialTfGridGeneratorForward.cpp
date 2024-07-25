#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSpatialTfGridGeneratorForward(cudnnHandle_t handle, const cudnnSpatialTransformerDescriptor_t stDesc, const void *theta, void *grid)
{
	cudnnStatus_t retval = cudnnSpatialTfGridGeneratorForward(handle, stDesc, theta, grid);
	return retval;
}