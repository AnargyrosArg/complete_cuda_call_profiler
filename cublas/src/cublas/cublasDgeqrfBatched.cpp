#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDgeqrfBatched)(cublasHandle_t, int, int, const double * const *, int, const double * const *, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDgeqrfBatched(cublasHandle_t handle, int m, int n, double * const Aarray[], int lda, double * const TauArray[], int *info, int batchSize) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDgeqrfBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDgeqrfBatched = (cublasStatus_t (*)(cublasHandle_t, int, int, const double * const *, int, const double * const *, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasDgeqrfBatched");
			fprintf(stderr, "wrapper_cublasDgeqrfBatched:%p\n", wrapper_cublasDgeqrfBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDgeqrfBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDgeqrfBatched(handle, m, n, Aarray, lda, TauArray, info, batchSize);
		return retval;
	}
}