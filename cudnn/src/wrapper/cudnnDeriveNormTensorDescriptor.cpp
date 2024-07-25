#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDeriveNormTensorDescriptor(cudnnTensorDescriptor_t derivedNormScaleBiasDesc, cudnnTensorDescriptor_t derivedNormMeanVarDesc, const cudnnTensorDescriptor_t xDesc, cudnnNormMode_t mode, int groupCnt)
{
	cudnnStatus_t retval = cudnnDeriveNormTensorDescriptor(derivedNormScaleBiasDesc, derivedNormMeanVarDesc, xDesc, mode, groupCnt);
	return retval;
}