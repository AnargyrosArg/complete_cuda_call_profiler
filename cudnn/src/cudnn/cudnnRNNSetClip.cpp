#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnRNNSetClip)(cudnnHandle_t, cudnnRNNDescriptor_t, cudnnRNNClipMode_t, cudnnNanPropagation_t, double, double);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnRNNSetClip(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, cudnnRNNClipMode_t clipMode, cudnnNanPropagation_t clipNanOpt, double lclip, double rclip) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnRNNSetClip)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnRNNSetClip = (cudnnStatus_t (*)(cudnnHandle_t, cudnnRNNDescriptor_t, cudnnRNNClipMode_t, cudnnNanPropagation_t, double, double)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnRNNSetClip");
			fprintf(stderr, "wrapper_cudnnRNNSetClip:%p\n", wrapper_cudnnRNNSetClip);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnRNNSetClip():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnRNNSetClip(handle, rnnDesc, clipMode, clipNanOpt, lclip, rclip);
		return retval;
	}
}

