#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetRNNMatrixMathType(cudnnRNNDescriptor_t rnnDesc, cudnnMathType_t mType)
{
	cudnnStatus_t retval = cudnnSetRNNMatrixMathType(rnnDesc, mType);
	return retval;
}