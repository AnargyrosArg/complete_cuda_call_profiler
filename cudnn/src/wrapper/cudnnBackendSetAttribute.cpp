#include <cudnn_backend.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnBackendSetAttribute(cudnnBackendDescriptor_t descriptor, cudnnBackendAttributeName_t attributeName, cudnnBackendAttributeType_t attributeType, int64_t elementCount, const void *arrayOfElements)
{
	cudnnStatus_t retval = cudnnBackendSetAttribute(descriptor, attributeName, attributeType, elementCount, arrayOfElements);
	return retval;
}