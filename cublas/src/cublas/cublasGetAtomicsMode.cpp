#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasGetAtomicsMode)(cublasHandle_t, cublasAtomicsMode_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasGetAtomicsMode(cublasHandle_t handle, cublasAtomicsMode_t *mode) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGetAtomicsMode)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGetAtomicsMode = (cublasStatus_t (*)(cublasHandle_t, cublasAtomicsMode_t *)) dlsym(libwrapper_handle, "wrapper_cublasGetAtomicsMode");
			fprintf(stderr, "wrapper_cublasGetAtomicsMode:%p\n", wrapper_cublasGetAtomicsMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGetAtomicsMode():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasGetAtomicsMode(handle, mode);
		return retval;
	}
}