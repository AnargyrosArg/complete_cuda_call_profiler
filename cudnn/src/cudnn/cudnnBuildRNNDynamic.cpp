#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnBuildRNNDynamic)(cudnnHandle_t, cudnnRNNDescriptor_t, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnBuildRNNDynamic(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, int miniBatch{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnBuildRNNDynamic)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnBuildRNNDynamic = (cudnnStatus_t (*)(cudnnHandle_t, cudnnRNNDescriptor_t, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnBuildRNNDynamic");
			fprintf(stderr, "wrapper_cudnnBuildRNNDynamic:%p\n", wrapper_cudnnBuildRNNDynamic);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnBuildRNNDynamic():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnBuildRNNDynamic(handle, rnnDesc, miniBatch);
		return retval;
	}
}

