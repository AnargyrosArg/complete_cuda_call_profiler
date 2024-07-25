#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCnnInferVersionCheck()
{
	cudnnStatus_t retval = cudnnCnnInferVersionCheck();
	return retval;
}