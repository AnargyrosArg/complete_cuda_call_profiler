#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpVV_bufferSize)(cusparseHandle_t, cusparseOperation_t, cusparseSpVecDescr_t, cusparseDnVecDescr_t, const void *, cudaDataType, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpVV_bufferSize(cusparseHandle_t handle, cusparseOperation_t opX, cusparseSpVecDescr_t vecX, cusparseDnVecDescr_t vecY, const void *result, cudaDataType computeType, size_t *bufferSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpVV_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpVV_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, cusparseSpVecDescr_t, cusparseDnVecDescr_t, const void *, cudaDataType, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpVV_bufferSize");
			fprintf(stderr, "wrapper_cusparseSpVV_bufferSize:%p\n", wrapper_cusparseSpVV_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpVV_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpVV_bufferSize(handle, opX, vecX, vecY, result, computeType, bufferSize);
		return retval;
	}
}