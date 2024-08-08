#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasGetSmCountTarget)(cublasHandle_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasGetSmCountTarget(cublasHandle_t handle, int *smCountTarget) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGetSmCountTarget)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGetSmCountTarget = (cublasStatus_t (*)(cublasHandle_t, int *)) dlsym(libwrapper_handle, "wrapper_cublasGetSmCountTarget");
			fprintf(stderr, "wrapper_cublasGetSmCountTarget:%p\n", wrapper_cublasGetSmCountTarget);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGetSmCountTarget():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasGetSmCountTarget(handle, smCountTarget);
		return retval;
	}
}