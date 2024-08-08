#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
const char * (*wrapper_cudnnGetErrorString)(cudnnStatus_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	const char * cudnnGetErrorString(cudnnStatus_t status{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetErrorString)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetErrorString = (const char * (*)(cudnnStatus_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetErrorString");
			fprintf(stderr, "wrapper_cudnnGetErrorString:%p\n", wrapper_cudnnGetErrorString);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetErrorString():%s\n", __dlerror);
			fflush(stderr);
		}
		const char * retval = wrapper_cudnnGetErrorString(status);
		return retval;
	}
}

