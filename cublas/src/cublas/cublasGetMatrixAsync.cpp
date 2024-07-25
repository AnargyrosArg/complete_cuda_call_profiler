#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasGetMatrixAsync)(int, int, int, const void *, int, void *, int, cudaStream_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasGetMatrixAsync(int rows, int cols, int elemSize, const void *A, int lda, void *B, int ldb, cudaStream_t stream) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGetMatrixAsync)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGetMatrixAsync = (cublasStatus_t (*)(int, int, int, const void *, int, void *, int, cudaStream_t)) dlsym(libwrapper_handle, "wrapper_cublasGetMatrixAsync");
			fprintf(stderr, "wrapper_cublasGetMatrixAsync:%p\n", wrapper_cublasGetMatrixAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGetMatrixAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasGetMatrixAsync(rows, cols, elemSize, A, lda, B, ldb, stream);
		return retval;
	}
}