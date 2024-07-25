#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatrixLayoutInit_internal)(cublasLtMatrixLayout_t, size_t, cudaDataType, uint64_t, uint64_t, int64_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatrixLayoutInit_internal(cublasLtMatrixLayout_t matLayout, size_t size, cudaDataType type, uint64_t rows, uint64_t cols, int64_t ld) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatrixLayoutInit_internal)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatrixLayoutInit_internal = (cublasStatus_t (*)(cublasLtMatrixLayout_t, size_t, cudaDataType, uint64_t, uint64_t, int64_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatrixLayoutInit_internal");
			fprintf(stderr, "wrapper_cublasLtMatrixLayoutInit_internal:%p\n", wrapper_cublasLtMatrixLayoutInit_internal);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatrixLayoutInit_internal():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatrixLayoutInit_internal(matLayout, size, type, rows, cols, ld);
		return retval;
	}
}