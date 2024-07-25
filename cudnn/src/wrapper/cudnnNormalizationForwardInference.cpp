#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnNormalizationForwardInference(cudnnHandle_t handle, cudnnNormMode_t mode, cudnnNormOps_t normOps, cudnnNormAlgo_t algo, const void *alpha, const void *beta, const cudnnTensorDescriptor_t xDesc, const void *x, const cudnnTensorDescriptor_t normScaleBiasDesc, const void *normScale, const void *normBias, const cudnnTensorDescriptor_t normMeanVarDesc, const void *estimatedMean, const void *estimatedVariance, const cudnnTensorDescriptor_t zDesc, const void *z, cudnnActivationDescriptor_t activationDesc, const cudnnTensorDescriptor_t yDesc, void *y, double epsilon, int groupCnt)
{
	cudnnStatus_t retval = cudnnNormalizationForwardInference(handle, mode, normOps, algo, alpha, beta, xDesc, x, normScaleBiasDesc, normScale, normBias, normMeanVarDesc, estimatedMean, estimatedVariance, zDesc, z, activationDesc, yDesc, y, epsilon, groupCnt);
	return retval;
}