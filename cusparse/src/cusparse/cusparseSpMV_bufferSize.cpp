#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMV_bufferSize)(cusparseHandle_t, cusparseOperation_t, const void *, cusparseSpMatDescr_t, cusparseDnVecDescr_t, const void *, cusparseDnVecDescr_t, cudaDataType, cusparseSpMVAlg_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMV_bufferSize(cusparseHandle_t handle, cusparseOperation_t opA, const void *alpha, cusparseSpMatDescr_t matA, cusparseDnVecDescr_t vecX, const void *beta, cusparseDnVecDescr_t vecY, cudaDataType computeType, cusparseSpMVAlg_t alg, size_t *bufferSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMV_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMV_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, const void *, cusparseSpMatDescr_t, cusparseDnVecDescr_t, const void *, cusparseDnVecDescr_t, cudaDataType, cusparseSpMVAlg_t, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMV_bufferSize");
			fprintf(stderr, "wrapper_cusparseSpMV_bufferSize:%p\n", wrapper_cusparseSpMV_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMV_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMV_bufferSize(handle, opA, alpha, matA, vecX, beta, vecY, computeType, alg, bufferSize);
		return retval;
	}
}