#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulDescDestroy)(cublasLtMatmulDesc_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulDescDestroy(cublasLtMatmulDesc_t matmulDesc){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulDescDestroy)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulDescDestroy = (cublasStatus_t (*)(cublasLtMatmulDesc_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulDescDestroy");
			fprintf(stderr, "wrapper_cublasLtMatmulDescDestroy:%p\n", wrapper_cublasLtMatmulDescDestroy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulDescDestroy():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulDescDestroy(matmulDesc);
		return retval;
	}
}