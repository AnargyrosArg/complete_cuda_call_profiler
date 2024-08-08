#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDnVecGet)(cusparseDnVecDescr_t, int64_t *, void **, cudaDataType *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDnVecGet(cusparseDnVecDescr_t dnVecDescr, int64_t *size, void **values, cudaDataType *valueType) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDnVecGet)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDnVecGet = (cusparseStatus_t (*)(cusparseDnVecDescr_t, int64_t *, void **, cudaDataType *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDnVecGet");
			fprintf(stderr, "wrapper_cusparseDnVecGet:%p\n", wrapper_cusparseDnVecGet);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDnVecGet():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDnVecGet(dnVecDescr, size, values, valueType);
		return retval;
	}
}