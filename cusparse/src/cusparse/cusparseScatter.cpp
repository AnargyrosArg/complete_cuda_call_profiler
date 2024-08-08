#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseScatter)(cusparseHandle_t, cusparseSpVecDescr_t, cusparseDnVecDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseScatter(cusparseHandle_t handle, cusparseSpVecDescr_t vecX, cusparseDnVecDescr_t vecY) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseScatter)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseScatter = (cusparseStatus_t (*)(cusparseHandle_t, cusparseSpVecDescr_t, cusparseDnVecDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseScatter");
			fprintf(stderr, "wrapper_cusparseScatter:%p\n", wrapper_cusparseScatter);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseScatter():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseScatter(handle, vecX, vecY);
		return retval;
	}
}