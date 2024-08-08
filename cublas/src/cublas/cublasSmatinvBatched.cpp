#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSmatinvBatched)(cublasHandle_t, int, const float * const*, int, float * const*, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSmatinvBatched(cublasHandle_t handle, int n, const float * const A[], int lda, float * const Ainv[], int lda_inv, int *info, int batchSize) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSmatinvBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSmatinvBatched = (cublasStatus_t (*)(cublasHandle_t, int, const float * const*, int, float * const*, int, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasSmatinvBatched");
			fprintf(stderr, "wrapper_cublasSmatinvBatched:%p\n", wrapper_cublasSmatinvBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSmatinvBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSmatinvBatched(handle, n, A, lda, Ainv, lda_inv, info, batchSize);
		return retval;
	}
}