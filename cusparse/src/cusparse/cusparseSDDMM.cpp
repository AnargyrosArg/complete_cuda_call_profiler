#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSDDMM)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseDnMatDescr_t, cusparseDnMatDescr_t, const void *, cusparseSpMatDescr_t, cudaDataType, cusparseSDDMMAlg_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSDDMM(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, const void *alpha, cusparseDnMatDescr_t matA, cusparseDnMatDescr_t matB, const void *beta, cusparseSpMatDescr_t matC, cudaDataType computeType, cusparseSDDMMAlg_t alg, void *externalBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSDDMM)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSDDMM = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseDnMatDescr_t, cusparseDnMatDescr_t, const void *, cusparseSpMatDescr_t, cudaDataType, cusparseSDDMMAlg_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSDDMM");
			fprintf(stderr, "wrapper_cusparseSDDMM:%p\n", wrapper_cusparseSDDMM);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSDDMM():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSDDMM(handle, opA, opB, alpha, matA, matB, beta, matC, computeType, alg, externalBuffer);
		return retval;
	}
}