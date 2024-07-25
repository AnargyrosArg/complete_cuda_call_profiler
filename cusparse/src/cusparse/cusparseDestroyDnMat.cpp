#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDestroyDnMat)(cusparseDnMatDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDestroyDnMat(cusparseDnMatDescr_t dnMatDescr) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDestroyDnMat)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDestroyDnMat = (cusparseStatus_t (*)(cusparseDnMatDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDestroyDnMat");
			fprintf(stderr, "wrapper_cusparseDestroyDnMat:%p\n", wrapper_cusparseDestroyDnMat);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDestroyDnMat():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDestroyDnMat(dnMatDescr);
		return retval;
	}
}