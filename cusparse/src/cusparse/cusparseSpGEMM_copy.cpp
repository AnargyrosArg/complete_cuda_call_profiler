#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpGEMM_copy)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseSpMatDescr_t, cusparseSpMatDescr_t, const void *, cusparseSpMatDescr_t, cudaDataType, cusparseSpGEMMAlg_t, cusparseSpGEMMDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpGEMM_copy(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, const void *alpha, cusparseSpMatDescr_t matA, cusparseSpMatDescr_t matB, const void *beta, cusparseSpMatDescr_t matC, cudaDataType computeType, cusparseSpGEMMAlg_t alg, cusparseSpGEMMDescr_t spgemmDescr) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpGEMM_copy)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpGEMM_copy = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseSpMatDescr_t, cusparseSpMatDescr_t, const void *, cusparseSpMatDescr_t, cudaDataType, cusparseSpGEMMAlg_t, cusparseSpGEMMDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpGEMM_copy");
			fprintf(stderr, "wrapper_cusparseSpGEMM_copy:%p\n", wrapper_cusparseSpGEMM_copy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpGEMM_copy():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpGEMM_copy(handle, opA, opB, alpha, matA, matB, beta, matC, computeType, alg, spgemmDescr);
		return retval;
	}
}