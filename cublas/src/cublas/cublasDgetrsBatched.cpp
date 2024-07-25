#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDgetrsBatched)(cublasHandle_t, cublasOperation_t, int, int, const double * const*, int, const int *, double * const*, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDgetrsBatched(cublasHandle_t handle, cublasOperation_t trans, int n, int nrhs, const double * const Aarray[], int lda, const int *devIpiv, double * const Barray[], int ldb, int *info, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDgetrsBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDgetrsBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, const double * const*, int, const int *, double * const*, int, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasDgetrsBatched");
			fprintf(stderr, "wrapper_cublasDgetrsBatched:%p\n", wrapper_cublasDgetrsBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDgetrsBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDgetrsBatched(handle, trans, n, nrhs, Aarray, lda, devIpiv, Barray, ldb, info, batchSize);
		return retval;
	}
}