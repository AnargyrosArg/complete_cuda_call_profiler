#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSpatialTfGridGeneratorBackward(cudnnHandle_t handle, const cudnnSpatialTransformerDescriptor_t stDesc, const void *dgrid, void *dtheta)
{
	cudnnStatus_t retval = cudnnSpatialTfGridGeneratorBackward(handle, stDesc, dgrid, dtheta);
	return retval;
}