#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCgetrsBatched)(cublasHandle_t, cublasOperation_t, int, int, const cuComplex * const *, int, const int *, cuComplex * const *, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCgetrsBatched(cublasHandle_t handle, cublasOperation_t trans, int n, int nrhs, const cuComplex * const Aarray[], int lda, const int *devIpiv, cuComplex * const Barray[], int ldb, int *info, int batchSize) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCgetrsBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCgetrsBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, const cuComplex * const *, int, const int *, cuComplex * const *, int, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasCgetrsBatched");
			fprintf(stderr, "wrapper_cublasCgetrsBatched:%p\n", wrapper_cublasCgetrsBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCgetrsBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCgetrsBatched(handle, trans, n, nrhs, Aarray, lda, devIpiv, Barray, ldb, info, batchSize);
		return retval;
	}
}