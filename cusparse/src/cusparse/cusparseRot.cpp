#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseRot)(cusparseHandle_t, const void *, const void *, cusparseSpVecDescr_t, cusparseDnVecDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseRot(cusparseHandle_t handle, const void *c_coeff, const void *s_coeff, cusparseSpVecDescr_t vecX, cusparseDnVecDescr_t vecY) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseRot)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseRot = (cusparseStatus_t (*)(cusparseHandle_t, const void *, const void *, cusparseSpVecDescr_t, cusparseDnVecDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseRot");
			fprintf(stderr, "wrapper_cusparseRot:%p\n", wrapper_cusparseRot);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseRot():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseRot(handle, c_coeff, s_coeff, vecX, vecY);
		return retval;
	}
}