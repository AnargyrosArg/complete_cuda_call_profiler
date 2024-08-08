#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetCallback)(unsigned, void *, cudnnCallback_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetCallback(unsigned mask, void *udata, cudnnCallback_t fptr{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetCallback)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetCallback = (cudnnStatus_t (*)(unsigned, void *, cudnnCallback_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetCallback");
			fprintf(stderr, "wrapper_cudnnSetCallback:%p\n", wrapper_cudnnSetCallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetCallback():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetCallback(mask, udata, fptr);
		return retval;
	}
}

