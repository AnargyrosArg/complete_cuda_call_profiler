#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatrixLayoutDestroy)(cublasLtMatrixLayout_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatrixLayoutDestroy(cublasLtMatrixLayout_t matLayout) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatrixLayoutDestroy)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatrixLayoutDestroy = (cublasStatus_t (*)(cublasLtMatrixLayout_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatrixLayoutDestroy");
			fprintf(stderr, "wrapper_cublasLtMatrixLayoutDestroy:%p\n", wrapper_cublasLtMatrixLayoutDestroy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatrixLayoutDestroy():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatrixLayoutDestroy(matLayout);
		return retval;
	}
}