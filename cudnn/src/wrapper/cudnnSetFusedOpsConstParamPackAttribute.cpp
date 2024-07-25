#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnSetFusedOpsConstParamPackAttribute(cudnnFusedOpsConstParamPack_t constPack, cudnnFusedOpsConstParamLabel_t paramLabel, const void *param)
{
	cudnnStatus_t retval = cudnnSetFusedOpsConstParamPackAttribute(constPack, paramLabel, param);
	return retval;
}