#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSparseToDense)(cusparseHandle_t, cusparseSpMatDescr_t, cusparseDnMatDescr_t, cusparseSparseToDenseAlg_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSparseToDense(cusparseHandle_t handle, cusparseSpMatDescr_t matA, cusparseDnMatDescr_t matB, cusparseSparseToDenseAlg_t alg, void *externalBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSparseToDense)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSparseToDense = (cusparseStatus_t (*)(cusparseHandle_t, cusparseSpMatDescr_t, cusparseDnMatDescr_t, cusparseSparseToDenseAlg_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSparseToDense");
			fprintf(stderr, "wrapper_cusparseSparseToDense:%p\n", wrapper_cusparseSparseToDense);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSparseToDense():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSparseToDense(handle, matA, matB, alg, externalBuffer);
		return retval;
	}
}