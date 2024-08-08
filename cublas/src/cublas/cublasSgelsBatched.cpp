#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSgelsBatched)(cublasHandle_t, cublasOperation_t, int, int, int, float * const*, int, float * const*, int, int *, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSgelsBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, int nrhs, float * const Aarray[], int lda, float * const Carray[], int ldc, int *info, int *devInfoArray, int batchSize) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSgelsBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSgelsBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, int, float * const*, int, float * const*, int, int *, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasSgelsBatched");
			fprintf(stderr, "wrapper_cublasSgelsBatched:%p\n", wrapper_cublasSgelsBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSgelsBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSgelsBatched(handle, trans, m, n, nrhs, Aarray, lda, Carray, ldc, info, devInfoArray, batchSize);
		return retval;
	}
}