#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
size_t (*wrapper_cudnnGetCudartVersion)();
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	size_t cudnnGetCudartVersion(){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetCudartVersion)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetCudartVersion = (size_t (*)()) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetCudartVersion");
			fprintf(stderr, "wrapper_cudnnGetCudartVersion:%p\n", wrapper_cudnnGetCudartVersion);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetCudartVersion():%s\n", __dlerror);
			fflush(stderr);
		}
		size_t retval = wrapper_cudnnGetCudartVersion();
		return retval;
	}
}

