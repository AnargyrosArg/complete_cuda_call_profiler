#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnDestroyFusedOpsConstParamPack(cudnnFusedOpsConstParamPack_t constPack)
{
	cudnnStatus_t retval = cudnnDestroyFusedOpsConstParamPack(constPack);
	return retval;
}