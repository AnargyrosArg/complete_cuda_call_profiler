#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroyFusedOpsPlan(cudnnFusedOpsPlan_t plan)
{
	cudnnStatus_t retval = cudnnDestroyFusedOpsPlan(plan);
	return retval;
}