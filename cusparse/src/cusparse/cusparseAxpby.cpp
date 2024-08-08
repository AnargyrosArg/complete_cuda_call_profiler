#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseAxpby)(cusparseHandle_t, const void *, cusparseSpVecDescr_t, const void *, cusparseDnVecDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseAxpby(cusparseHandle_t handle, const void *alpha, cusparseSpVecDescr_t vecX, const void *beta, cusparseDnVecDescr_t vecY) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseAxpby)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseAxpby = (cusparseStatus_t (*)(cusparseHandle_t, const void *, cusparseSpVecDescr_t, const void *, cusparseDnVecDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseAxpby");
			fprintf(stderr, "wrapper_cusparseAxpby:%p\n", wrapper_cusparseAxpby);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseAxpby():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseAxpby(handle, alpha, vecX, beta, vecY);
		return retval;
	}
}