#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetCallback)(unsigned *, void **, cudnnCallback_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetCallback(unsigned *mask, void **udata, cudnnCallback_t *fptr) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetCallback)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetCallback = (cudnnStatus_t (*)(unsigned *, void **, cudnnCallback_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetCallback");
			fprintf(stderr, "wrapper_cudnnGetCallback:%p\n", wrapper_cudnnGetCallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetCallback():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetCallback(mask, udata, fptr);
		return retval;
	}
}

