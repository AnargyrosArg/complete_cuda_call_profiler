#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseGather)(cusparseHandle_t, cusparseDnVecDescr_t, cusparseSpVecDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseGather(cusparseHandle_t handle, cusparseDnVecDescr_t vecY, cusparseSpVecDescr_t vecX) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseGather)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseGather = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDnVecDescr_t, cusparseSpVecDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseGather");
			fprintf(stderr, "wrapper_cusparseGather:%p\n", wrapper_cusparseGather);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseGather():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseGather(handle, vecY, vecX);
		return retval;
	}
}