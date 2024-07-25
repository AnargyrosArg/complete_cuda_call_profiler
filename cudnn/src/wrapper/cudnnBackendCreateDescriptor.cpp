#include <cudnn_backend.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnBackendCreateDescriptor(cudnnBackendDescriptorType_t descriptorType, cudnnBackendDescriptor_t *descriptor)
{
	cudnnStatus_t retval = cudnnBackendCreateDescriptor(descriptorType, descriptor);
	return retval;
}