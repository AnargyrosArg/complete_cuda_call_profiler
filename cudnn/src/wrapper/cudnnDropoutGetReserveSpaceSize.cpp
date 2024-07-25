#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDropoutGetReserveSpaceSize(cudnnTensorDescriptor_t xdesc, size_t *sizeInBytes)
{
	cudnnStatus_t retval = cudnnDropoutGetReserveSpaceSize(xdesc, sizeInBytes);
	return retval;
}