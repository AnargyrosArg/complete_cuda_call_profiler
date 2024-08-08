#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseConstrainedGeMM)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseDnMatDescr_t, cusparseDnMatDescr_t, const void *, cusparseSpMatDescr_t, cudaDataType, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseConstrainedGeMM(cusparseHandle_t handle, cusparseOperation_t opA, cusparseOperation_t opB, const void *alpha, cusparseDnMatDescr_t matA, cusparseDnMatDescr_t matB, const void *beta, cusparseSpMatDescr_t matC, cudaDataType computeType, void *externalBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseConstrainedGeMM)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseConstrainedGeMM = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, cusparseOperation_t, const void *, cusparseDnMatDescr_t, cusparseDnMatDescr_t, const void *, cusparseSpMatDescr_t, cudaDataType, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseConstrainedGeMM");
			fprintf(stderr, "wrapper_cusparseConstrainedGeMM:%p\n", wrapper_cusparseConstrainedGeMM);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseConstrainedGeMM():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseConstrainedGeMM(handle, opA, opB, alpha, matA, matB, beta, matC, computeType, externalBuffer);
		return retval;
	}
}