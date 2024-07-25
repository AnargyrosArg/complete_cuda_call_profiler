#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSetMatrix)(int, int, int, const void *, int, void *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSetMatrix(int rows, int cols, int elemSize, const void *A, int lda, void *B, int ldb) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSetMatrix)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSetMatrix = (cublasStatus_t (*)(int, int, int, const void *, int, void *, int)) dlsym(libwrapper_handle, "wrapper_cublasSetMatrix");
			fprintf(stderr, "wrapper_cublasSetMatrix:%p\n", wrapper_cublasSetMatrix);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSetMatrix():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSetMatrix(rows, cols, elemSize, A, lda, B, ldb);
		return retval;
	}
}