#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDestroySpVec)(cusparseSpVecDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDestroySpVec(cusparseSpVecDescr_t spVecDescr) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDestroySpVec)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDestroySpVec = (cusparseStatus_t (*)(cusparseSpVecDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDestroySpVec");
			fprintf(stderr, "wrapper_cusparseDestroySpVec:%p\n", wrapper_cusparseDestroySpVec);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDestroySpVec():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDestroySpVec(spVecDescr);
		return retval;
	}
}