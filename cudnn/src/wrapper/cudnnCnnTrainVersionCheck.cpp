#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnCnnTrainVersionCheck()
{
	cudnnStatus_t retval = cudnnCnnTrainVersionCheck();
	return retval;
}