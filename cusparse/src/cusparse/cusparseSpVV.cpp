#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpVV)(cusparseHandle_t, cusparseOperation_t, cusparseSpVecDescr_t, cusparseDnVecDescr_t, void *, cudaDataType, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpVV(cusparseHandle_t handle, cusparseOperation_t opX, cusparseSpVecDescr_t vecX, cusparseDnVecDescr_t vecY, void *result, cudaDataType computeType, void *externalBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpVV)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpVV = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, cusparseSpVecDescr_t, cusparseDnVecDescr_t, void *, cudaDataType, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpVV");
			fprintf(stderr, "wrapper_cusparseSpVV:%p\n", wrapper_cusparseSpVV);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpVV():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpVV(handle, opX, vecX, vecY, result, computeType, externalBuffer);
		return retval;
	}
}