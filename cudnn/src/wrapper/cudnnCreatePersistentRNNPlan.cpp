#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCreatePersistentRNNPlan(cudnnRNNDescriptor_t rnnDesc, const int minibatch, const cudnnDataType_t dataType, cudnnPersistentRNNPlan_t *plan)
{
	cudnnStatus_t retval = cudnnCreatePersistentRNNPlan(rnnDesc, minibatch, dataType, plan);
	return retval;
}