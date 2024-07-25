#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetTensorTransformDescriptor(cudnnTensorTransformDescriptor_t transformDesc, uint32_t nbDimsRequested, cudnnTensorFormat_t *destFormat, int32_t padBeforeA[], int32_t padAfterA[], uint32_t foldA[], cudnnFoldingDirection_t *direction)
{
	cudnnStatus_t retval = cudnnGetTensorTransformDescriptor(transformDesc, nbDimsRequested, destFormat, padBeforeA, padAfterA, foldA, direction);
	return retval;
}