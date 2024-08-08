#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSetAtomicsMode)(cublasHandle_t, cublasAtomicsMode_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSetAtomicsMode(cublasHandle_t handle, cublasAtomicsMode_t mode) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSetAtomicsMode)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSetAtomicsMode = (cublasStatus_t (*)(cublasHandle_t, cublasAtomicsMode_t)) dlsym(libwrapper_handle, "wrapper_cublasSetAtomicsMode");
			fprintf(stderr, "wrapper_cublasSetAtomicsMode:%p\n", wrapper_cublasSetAtomicsMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSetAtomicsMode():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSetAtomicsMode(handle, mode);
		return retval;
	}
}