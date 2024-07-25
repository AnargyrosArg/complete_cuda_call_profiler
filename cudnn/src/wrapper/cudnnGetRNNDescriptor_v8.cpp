#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetRNNDescriptor_v8(cudnnRNNDescriptor_t rnnDesc, cudnnRNNAlgo_t *algo, cudnnRNNMode_t *cellMode, cudnnRNNBiasMode_t *biasMode, cudnnDirectionMode_t *dirMode, cudnnRNNInputMode_t *inputMode, cudnnDataType_t *dataType, cudnnDataType_t *mathPrec, cudnnMathType_t *mathType, int32_t *inputSize, int32_t *hiddenSize, int32_t *projSize, int32_t *numLayers, cudnnDropoutDescriptor_t *dropoutDesc, uint32_t *auxFlags)
{
	cudnnStatus_t retval = cudnnGetRNNDescriptor_v8(rnnDesc, algo, cellMode, biasMode, dirMode, inputMode, dataType, mathPrec, mathType, inputSize, hiddenSize, projSize, numLayers, dropoutDesc, auxFlags);
	return retval;
}