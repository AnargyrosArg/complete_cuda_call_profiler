#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDnrm2_v2)(cublasHandle_t, int, const double *, int, double *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDnrm2_v2(cublasHandle_t handle, int n, const double *x, int incx, double *result) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDnrm2_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDnrm2_v2 = (cublasStatus_t (*)(cublasHandle_t, int, const double *, int, double *)) dlsym(libwrapper_handle, "wrapper_cublasDnrm2_v2");
			fprintf(stderr, "wrapper_cublasDnrm2_v2:%p\n", wrapper_cublasDnrm2_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDnrm2_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDnrm2_v2(handle, n, x, incx, result);
		return retval;
	}
}