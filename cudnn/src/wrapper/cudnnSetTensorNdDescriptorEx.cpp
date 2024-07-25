#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetTensorNdDescriptorEx(cudnnTensorDescriptor_t tensorDesc, cudnnTensorFormat_t format, cudnnDataType_t dataType, int nbDims, const int dimA[])
{
	cudnnStatus_t retval = cudnnSetTensorNdDescriptorEx(tensorDesc, format, dataType, nbDims, dimA);
	return retval;
}