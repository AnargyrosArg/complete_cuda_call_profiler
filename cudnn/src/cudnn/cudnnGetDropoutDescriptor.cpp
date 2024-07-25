#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetDropoutDescriptor)(cudnnDropoutDescriptor_t, cudnnHandle_t, float *, void **, unsigned long long *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetDropoutDescriptor(cudnnDropoutDescriptor_t dropoutDesc, cudnnHandle_t handle, float *dropout, void **states, unsigned long long *seed) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetDropoutDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetDropoutDescriptor = (cudnnStatus_t (*)(cudnnDropoutDescriptor_t, cudnnHandle_t, float *, void **, unsigned long long *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetDropoutDescriptor");
			fprintf(stderr, "wrapper_cudnnGetDropoutDescriptor:%p\n", wrapper_cudnnGetDropoutDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetDropoutDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetDropoutDescriptor(dropoutDesc, handle, dropout, states, seed);
		return retval;
	}
}

