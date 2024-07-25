#include <cudnn_backend.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnBackendInitialize(cudnnBackendDescriptor_t descriptor)
{
	cudnnStatus_t retval = cudnnBackendInitialize(descriptor);
	return retval;
}