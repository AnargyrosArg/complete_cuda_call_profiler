#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetRNNProjectionLayers)(cudnnHandle_t, const cudnnRNNDescriptor_t, int *, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetRNNProjectionLayers(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, int *recProjSize, int *outProjSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetRNNProjectionLayers)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetRNNProjectionLayers = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnRNNDescriptor_t, int *, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetRNNProjectionLayers");
			fprintf(stderr, "wrapper_cudnnGetRNNProjectionLayers:%p\n", wrapper_cudnnGetRNNProjectionLayers);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetRNNProjectionLayers():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetRNNProjectionLayers(handle, rnnDesc, recProjSize, outProjSize);
		return retval;
	}
}

