#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnGetFusedOpsConstParamPackAttribute(const cudnnFusedOpsConstParamPack_t constPack, cudnnFusedOpsConstParamLabel_t paramLabel, void *param, int *isNULL)
{
	cudnnStatus_t retval = cudnnGetFusedOpsConstParamPackAttribute(constPack, paramLabel, param, isNULL);
	return retval;
}