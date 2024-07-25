#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetFilterNdDescriptor(cudnnFilterDescriptor_t filterDesc, cudnnDataType_t dataType, cudnnTensorFormat_t format, int nbDims, const int filterDimA[])
{
	cudnnStatus_t retval = cudnnSetFilterNdDescriptor(filterDesc, dataType, format, nbDims, filterDimA);
	return retval;
}