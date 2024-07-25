#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateFilterDescriptor)(cudnnFilterDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateFilterDescriptor(cudnnFilterDescriptor_t *filterDesc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateFilterDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateFilterDescriptor = (cudnnStatus_t (*)(cudnnFilterDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateFilterDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateFilterDescriptor:%p\n", wrapper_cudnnCreateFilterDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateFilterDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateFilterDescriptor(filterDesc);
		return retval;
	}
}

