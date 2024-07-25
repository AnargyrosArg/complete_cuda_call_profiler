#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroySpatialTransformerDescriptor(cudnnSpatialTransformerDescriptor_t stDesc)
{
	cudnnStatus_t retval = cudnnDestroySpatialTransformerDescriptor(stDesc);
	return retval;
}