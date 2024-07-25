#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnInitTransformDest(const cudnnTensorTransformDescriptor_t transformDesc, const cudnnTensorDescriptor_t srcDesc, cudnnTensorDescriptor_t destDesc, size_t *destSizeInBytes)
{
	cudnnStatus_t retval = cudnnInitTransformDest(transformDesc, srcDesc, destDesc, destSizeInBytes);
	return retval;
}