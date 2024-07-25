#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cudnnStatus_t wrapper_cudnnRNNGetClip(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, cudnnRNNClipMode_t *clipMode, cudnnNanPropagation_t *clipNanOpt, double *lclip, double *rclip)
{
	cudnnStatus_t retval = cudnnRNNGetClip(handle, rnnDesc, clipMode, clipNanOpt, lclip, rclip);
	return retval;
}