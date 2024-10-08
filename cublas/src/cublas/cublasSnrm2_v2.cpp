#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSnrm2_v2)(cublasHandle_t, int, const float *, int, float *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSnrm2_v2(cublasHandle_t handle, int n, const float *x, int incx, float *result) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSnrm2_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSnrm2_v2 = (cublasStatus_t (*)(cublasHandle_t, int, const float *, int, float *)) dlsym(libwrapper_handle, "wrapper_cublasSnrm2_v2");
			fprintf(stderr, "wrapper_cublasSnrm2_v2:%p\n", wrapper_cublasSnrm2_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSnrm2_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSnrm2_v2(handle, n, x, incx, result);
		return retval;
	}
}