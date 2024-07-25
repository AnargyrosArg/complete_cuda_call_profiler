#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSrotmg_v2)(cublasHandle_t, float *, float *, float *, const float *, float *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSrotmg_v2(cublasHandle_t handle, float *d1, float *d2, float *x1, const float *y1, float *param) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSrotmg_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSrotmg_v2 = (cublasStatus_t (*)(cublasHandle_t, float *, float *, float *, const float *, float *)) dlsym(libwrapper_handle, "wrapper_cublasSrotmg_v2");
			fprintf(stderr, "wrapper_cublasSrotmg_v2:%p\n", wrapper_cublasSrotmg_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSrotmg_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSrotmg_v2(handle, d1, d2, x1, y1, param);
		return retval;
	}
}