#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpGEMMreuse_copy)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, cusparseSpMatDescr_t, cusparseSpMatDescr_t, cusparseSpMatDescr_t, cusparseSpGEMMAlg_t, cusparseSpGEMMDescr_t, size_t *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpGEMMreuse_copy(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, cusparseSpMatDescr_t matA, cusparseSpMatDescr_t matB, cusparseSpMatDescr_t matC, cusparseSpGEMMAlg_t alg, cusparseSpGEMMDescr_t spgemmDescr, size_t *bufferSize5, void *externalBuffer5) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpGEMMreuse_copy)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpGEMMreuse_copy = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, cusparseSpMatDescr_t, cusparseSpMatDescr_t, cusparseSpMatDescr_t, cusparseSpGEMMAlg_t, cusparseSpGEMMDescr_t, size_t *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpGEMMreuse_copy");
			fprintf(stderr, "wrapper_cusparseSpGEMMreuse_copy:%p\n", wrapper_cusparseSpGEMMreuse_copy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpGEMMreuse_copy():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpGEMMreuse_copy(handle, opA, opB, matA, matB, matC, alg, spgemmDescr, bufferSize5, externalBuffer5);
		return retval;
	}
}