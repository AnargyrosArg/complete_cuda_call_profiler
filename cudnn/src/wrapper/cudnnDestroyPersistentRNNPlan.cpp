#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroyPersistentRNNPlan(cudnnPersistentRNNPlan_t plan)
{
	cudnnStatus_t retval = cudnnDestroyPersistentRNNPlan(plan);
	return retval;
}