#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSetMatrixAsync)(int, int, int, const void *, int, void *, int, cudaStream_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSetMatrixAsync(int rows, int cols, int elemSize, const void *A, int lda, void *B, int ldb, cudaStream_t stream) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSetMatrixAsync)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSetMatrixAsync = (cublasStatus_t (*)(int, int, int, const void *, int, void *, int, cudaStream_t)) dlsym(libwrapper_handle, "wrapper_cublasSetMatrixAsync");
			fprintf(stderr, "wrapper_cublasSetMatrixAsync:%p\n", wrapper_cublasSetMatrixAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSetMatrixAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSetMatrixAsync(rows, cols, elemSize, A, lda, B, ldb, stream);
		return retval;
	}
}