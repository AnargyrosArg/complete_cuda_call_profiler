#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnAdvInferVersionCheck()
{
	cudnnStatus_t retval = cudnnAdvInferVersionCheck();
	return retval;
}