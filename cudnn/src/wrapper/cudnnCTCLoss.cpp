#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCTCLoss(cudnnHandle_t handle, const cudnnTensorDescriptor_t probsDesc, const void *probs, const int hostLabels[], const int hostLabelLengths[], const int hostInputLengths[], void *costs, const cudnnTensorDescriptor_t gradientsDesc, void *gradients, cudnnCTCLossAlgo_t algo, cudnnCTCLossDescriptor_t ctcLossDesc, void *workspace, size_t workSpaceSizeInBytes)
{
	cudnnStatus_t retval = cudnnCTCLoss(handle, probsDesc, probs, hostLabels, hostLabelLengths, hostInputLengths, costs, gradientsDesc, gradients, algo, ctcLossDesc, workspace, workSpaceSizeInBytes);
	return retval;
}