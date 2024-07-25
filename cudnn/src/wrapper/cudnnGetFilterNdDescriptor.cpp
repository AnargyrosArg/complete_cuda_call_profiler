#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetFilterNdDescriptor(const cudnnFilterDescriptor_t filterDesc, int nbDimsRequested, cudnnDataType_t *dataType, cudnnTensorFormat_t *format, int *nbDims, int filterDimA[])
{
	cudnnStatus_t retval = cudnnGetFilterNdDescriptor(filterDesc, nbDimsRequested, dataType, format, nbDims, filterDimA);
	return retval;
}