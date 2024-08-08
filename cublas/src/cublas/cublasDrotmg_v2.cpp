#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDrotmg_v2)(cublasHandle_t, double *, double *, double *, const double *, double *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDrotmg_v2(cublasHandle_t handle, double *d1, double *d2, double *x1, const double *y1, double *param) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDrotmg_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDrotmg_v2 = (cublasStatus_t (*)(cublasHandle_t, double *, double *, double *, const double *, double *)) dlsym(libwrapper_handle, "wrapper_cublasDrotmg_v2");
			fprintf(stderr, "wrapper_cublasDrotmg_v2:%p\n", wrapper_cublasDrotmg_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDrotmg_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDrotmg_v2(handle, d1, d2, x1, y1, param);
		return retval;
	}
}