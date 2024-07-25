#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnRestoreDropoutDescriptor)(cudnnDropoutDescriptor_t, cudnnHandle_t, float, void *, size_t, unsigned long long);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnRestoreDropoutDescriptor(cudnnDropoutDescriptor_t dropoutDesc, cudnnHandle_t handle, float dropout, void *states, size_t stateSizeInBytes, unsigned long long seed) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnRestoreDropoutDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnRestoreDropoutDescriptor = (cudnnStatus_t (*)(cudnnDropoutDescriptor_t, cudnnHandle_t, float, void *, size_t, unsigned long long)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnRestoreDropoutDescriptor");
			fprintf(stderr, "wrapper_cudnnRestoreDropoutDescriptor:%p\n", wrapper_cudnnRestoreDropoutDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnRestoreDropoutDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnRestoreDropoutDescriptor(dropoutDesc, handle, dropout, states, stateSizeInBytes, seed);
		return retval;
	}
}

