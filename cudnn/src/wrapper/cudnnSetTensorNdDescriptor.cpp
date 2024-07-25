#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetTensorNdDescriptor(cudnnTensorDescriptor_t tensorDesc, cudnnDataType_t dataType, int nbDims, const int dimA[], const int strideA[])
{
	cudnnStatus_t retval = cudnnSetTensorNdDescriptor(tensorDesc, dataType, nbDims, dimA, strideA);
	return retval;
}