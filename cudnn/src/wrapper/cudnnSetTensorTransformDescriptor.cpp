#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetTensorTransformDescriptor(cudnnTensorTransformDescriptor_t transformDesc, const uint32_t nbDims, const cudnnTensorFormat_t destFormat, const int32_t padBeforeA[], const int32_t padAfterA[], const uint32_t foldA[], const cudnnFoldingDirection_t direction)
{
	cudnnStatus_t retval = cudnnSetTensorTransformDescriptor(transformDesc, nbDims, destFormat, padBeforeA, padAfterA, foldA, direction);
	return retval;
}