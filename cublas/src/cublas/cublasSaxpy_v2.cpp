#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSaxpy_v2)(cublasHandle_t, int, const float *, const float *, int, float *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSaxpy_v2(cublasHandle_t handle, int n, const float *alpha, const float *x, int incx, float *y, int incy) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSaxpy_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSaxpy_v2 = (cublasStatus_t (*)(cublasHandle_t, int, const float *, const float *, int, float *, int)) dlsym(libwrapper_handle, "wrapper_cublasSaxpy_v2");
			fprintf(stderr, "wrapper_cublasSaxpy_v2:%p\n", wrapper_cublasSaxpy_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSaxpy_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSaxpy_v2(handle, n, alpha, x, incx, y, incy);
		return retval;
	}
}