#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSparseToDense_bufferSize)(cusparseHandle_t, cusparseSpMatDescr_t, cusparseDnMatDescr_t, cusparseSparseToDenseAlg_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSparseToDense_bufferSize(cusparseHandle_t handle, cusparseSpMatDescr_t matA, cusparseDnMatDescr_t matB, cusparseSparseToDenseAlg_t alg, size_t *bufferSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSparseToDense_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSparseToDense_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, cusparseSpMatDescr_t, cusparseDnMatDescr_t, cusparseSparseToDenseAlg_t, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSparseToDense_bufferSize");
			fprintf(stderr, "wrapper_cusparseSparseToDense_bufferSize:%p\n", wrapper_cusparseSparseToDense_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSparseToDense_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSparseToDense_bufferSize(handle, matA, matB, alg, bufferSize);
		return retval;
	}
}