#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetDropoutDescriptor)(cudnnDropoutDescriptor_t, cudnnHandle_t, float, void *, size_t, unsigned long long);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetDropoutDescriptor(cudnnDropoutDescriptor_t dropoutDesc, cudnnHandle_t handle, float dropout, void *states, size_t stateSizeInBytes, unsigned long long seed){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetDropoutDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetDropoutDescriptor = (cudnnStatus_t (*)(cudnnDropoutDescriptor_t, cudnnHandle_t, float, void *, size_t, unsigned long long)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetDropoutDescriptor");
			fprintf(stderr, "wrapper_cudnnSetDropoutDescriptor:%p\n", wrapper_cudnnSetDropoutDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetDropoutDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetDropoutDescriptor(dropoutDesc, handle, dropout, states, stateSizeInBytes, seed);
		return retval;
	}
}

