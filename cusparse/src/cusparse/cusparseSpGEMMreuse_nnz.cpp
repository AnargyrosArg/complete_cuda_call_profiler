#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpGEMMreuse_nnz)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, cusparseSpMatDescr_t, cusparseSpMatDescr_t, cusparseSpMatDescr_t, cusparseSpGEMMAlg_t, cusparseSpGEMMDescr_t, size_t *, void *, size_t *, void *, size_t *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpGEMMreuse_nnz(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, cusparseSpMatDescr_t matA, cusparseSpMatDescr_t matB, cusparseSpMatDescr_t matC, cusparseSpGEMMAlg_t alg, cusparseSpGEMMDescr_t spgemmDescr, size_t *bufferSize2, void *externalBuffer2, size_t *bufferSize3, void *externalBuffer3, size_t *bufferSize4, void *externalBuffer4) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpGEMMreuse_nnz)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpGEMMreuse_nnz = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, cusparseSpMatDescr_t, cusparseSpMatDescr_t, cusparseSpMatDescr_t, cusparseSpGEMMAlg_t, cusparseSpGEMMDescr_t, size_t *, void *, size_t *, void *, size_t *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpGEMMreuse_nnz");
			fprintf(stderr, "wrapper_cusparseSpGEMMreuse_nnz:%p\n", wrapper_cusparseSpGEMMreuse_nnz);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpGEMMreuse_nnz():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpGEMMreuse_nnz(handle, opA, opB, matA, matB, matC, alg, spgemmDescr, bufferSize2, externalBuffer2, bufferSize3, externalBuffer3, bufferSize4, externalBuffer4);
		return retval;
	}
}