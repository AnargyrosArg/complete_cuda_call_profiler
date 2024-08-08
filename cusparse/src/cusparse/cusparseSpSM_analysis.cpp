#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpSM_analysis)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseSpMatDescr_t, cusparseDnMatDescr_t, cusparseDnMatDescr_t, cudaDataType, cusparseSpSMAlg_t, cusparseSpSMDescr_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpSM_analysis(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, const void *alpha, cusparseSpMatDescr_t matA, cusparseDnMatDescr_t matB, cusparseDnMatDescr_t matC, cudaDataType computeType, cusparseSpSMAlg_t alg, cusparseSpSMDescr_t spsmDescr, void *externalBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpSM_analysis)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpSM_analysis = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseSpMatDescr_t, cusparseDnMatDescr_t, cusparseDnMatDescr_t, cudaDataType, cusparseSpSMAlg_t, cusparseSpSMDescr_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpSM_analysis");
			fprintf(stderr, "wrapper_cusparseSpSM_analysis:%p\n", wrapper_cusparseSpSM_analysis);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpSM_analysis():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpSM_analysis(handle, opA, opB, alpha, matA, matB, matC, computeType, alg, spsmDescr, externalBuffer);
		return retval;
	}
}