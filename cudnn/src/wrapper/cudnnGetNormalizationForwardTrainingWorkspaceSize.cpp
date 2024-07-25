#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetNormalizationForwardTrainingWorkspaceSize(cudnnHandle_t handle, cudnnNormMode_t mode, cudnnNormOps_t normOps, cudnnNormAlgo_t algo, const cudnnTensorDescriptor_t xDesc, const cudnnTensorDescriptor_t zDesc, const cudnnTensorDescriptor_t yDesc, const cudnnTensorDescriptor_t normScaleBiasDesc, const cudnnActivationDescriptor_t activationDesc, const cudnnTensorDescriptor_t normMeanVarDesc, size_t *sizeInBytes, int groupCnt)
{
	cudnnStatus_t retval = cudnnGetNormalizationForwardTrainingWorkspaceSize(handle, mode, normOps, algo, xDesc, zDesc, yDesc, normScaleBiasDesc, activationDesc, normMeanVarDesc, sizeInBytes, groupCnt);
	return retval;
}