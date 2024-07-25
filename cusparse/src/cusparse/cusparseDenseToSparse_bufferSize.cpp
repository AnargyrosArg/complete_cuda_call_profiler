#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDenseToSparse_bufferSize)(cusparseHandle_t, cusparseDnMatDescr_t, cusparseSpMatDescr_t, cusparseDenseToSparseAlg_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDenseToSparse_bufferSize(cusparseHandle_t handle, cusparseDnMatDescr_t matA, cusparseSpMatDescr_t matB, cusparseDenseToSparseAlg_t alg, size_t *bufferSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDenseToSparse_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDenseToSparse_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDnMatDescr_t, cusparseSpMatDescr_t, cusparseDenseToSparseAlg_t, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDenseToSparse_bufferSize");
			fprintf(stderr, "wrapper_cusparseDenseToSparse_bufferSize:%p\n", wrapper_cusparseDenseToSparse_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDenseToSparse_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDenseToSparse_bufferSize(handle, matA, matB, alg, bufferSize);
		return retval;
	}
}