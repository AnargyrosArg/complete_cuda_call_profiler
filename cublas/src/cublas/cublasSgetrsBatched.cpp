#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSgetrsBatched)(cublasHandle_t, cublasOperation_t, int, int, const float * const *, int, const int *, float * const *, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSgetrsBatched(cublasHandle_t handle, cublasOperation_t trans, int n, int nrhs, const float * const Aarray[], int lda, const int *devIpiv, float * const Barray[], int ldb, int *info, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSgetrsBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSgetrsBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, const float * const *, int, const int *, float * const *, int, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasSgetrsBatched");
			fprintf(stderr, "wrapper_cublasSgetrsBatched:%p\n", wrapper_cublasSgetrsBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSgetrsBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSgetrsBatched(handle, trans, n, nrhs, Aarray, lda, devIpiv, Barray, ldb, info, batchSize);
		return retval;
	}
}