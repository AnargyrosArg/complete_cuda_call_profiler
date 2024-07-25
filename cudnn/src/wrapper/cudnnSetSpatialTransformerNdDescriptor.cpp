#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetSpatialTransformerNdDescriptor(cudnnSpatialTransformerDescriptor_t stDesc, cudnnSamplerType_t samplerType, cudnnDataType_t dataType, const int nbDims, const int dimA[])
{
	cudnnStatus_t retval = cudnnSetSpatialTransformerNdDescriptor(stDesc, samplerType, dataType, nbDims, dimA);
	return retval;
}