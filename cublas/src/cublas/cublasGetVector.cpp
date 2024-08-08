#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasGetVector)(int, int, const void *, int, void *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasGetVector(int n, int elemSize, const void *x, int incx, void *y, int incy) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGetVector)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGetVector = (cublasStatus_t (*)(int, int, const void *, int, void *, int)) dlsym(libwrapper_handle, "wrapper_cublasGetVector");
			fprintf(stderr, "wrapper_cublasGetVector:%p\n", wrapper_cublasGetVector);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGetVector():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasGetVector(n, elemSize, x, incx, y, incy);
		return retval;
	}
}