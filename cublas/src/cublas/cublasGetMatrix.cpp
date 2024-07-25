#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasGetMatrix)(int, int, int, const void *, int, void *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasGetMatrix(int rows, int cols, int elemSize, const void *A, int lda, void *B, int ldb) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGetMatrix)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGetMatrix = (cublasStatus_t (*)(int, int, int, const void *, int, void *, int)) dlsym(libwrapper_handle, "wrapper_cublasGetMatrix");
			fprintf(stderr, "wrapper_cublasGetMatrix:%p\n", wrapper_cublasGetMatrix);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGetMatrix():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasGetMatrix(rows, cols, elemSize, A, lda, B, ldb);
		return retval;
	}
}