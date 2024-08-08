#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetRNNProjectionLayers)(cudnnHandle_t, cudnnRNNDescriptor_t, const int, const int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetRNNProjectionLayers(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, const int recProjSize, const int outProjSize{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetRNNProjectionLayers)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetRNNProjectionLayers = (cudnnStatus_t (*)(cudnnHandle_t, cudnnRNNDescriptor_t, const int, const int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetRNNProjectionLayers");
			fprintf(stderr, "wrapper_cudnnSetRNNProjectionLayers:%p\n", wrapper_cudnnSetRNNProjectionLayers);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetRNNProjectionLayers():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetRNNProjectionLayers(handle, rnnDesc, recProjSize, outProjSize);
		return retval;
	}
}

