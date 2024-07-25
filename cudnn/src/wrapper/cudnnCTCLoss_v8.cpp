#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCTCLoss_v8(cudnnHandle_t handle, cudnnCTCLossAlgo_t algo, cudnnCTCLossDescriptor_t ctcLossDesc, const cudnnTensorDescriptor_t probsDesc, const void *probs, const int labels[], const int labelLengths[], const int inputLengths[], void *costs, const cudnnTensorDescriptor_t gradientsDesc, void *gradients, size_t workSpaceSizeInBytes, void *workspace)
{
	cudnnStatus_t retval = cudnnCTCLoss_v8(handle, algo, ctcLossDesc, probsDesc, probs, labels, labelLengths, inputLengths, costs, gradientsDesc, gradients, workSpaceSizeInBytes, workspace);
	return retval;
}