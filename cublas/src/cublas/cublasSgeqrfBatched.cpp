#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSgeqrfBatched)(cublasHandle_t, int, int, float * const*, int, float * const*, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSgeqrfBatched(cublasHandle_t handle, int m, int n, float * const Aarray[], int lda, float * const TauArray[], int *info, int batchSize) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSgeqrfBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSgeqrfBatched = (cublasStatus_t (*)(cublasHandle_t, int, int, float * const*, int, float * const*, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasSgeqrfBatched");
			fprintf(stderr, "wrapper_cublasSgeqrfBatched:%p\n", wrapper_cublasSgeqrfBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSgeqrfBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSgeqrfBatched(handle, m, n, Aarray, lda, TauArray, info, batchSize);
		return retval;
	}
}