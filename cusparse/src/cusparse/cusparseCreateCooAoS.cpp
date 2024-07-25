#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCreateCooAoS)(cusparseSpMatDescr_t *, int64_t, int64_t, int64_t, void *, void *, cusparseIndexType_t, cusparseIndexBase_t, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCreateCooAoS(cusparseSpMatDescr_t *spMatDescr, int64_t rows, int64_t cols, int64_t nnz, void *cooInd, void *cooValues, cusparseIndexType_t cooIdxType, cusparseIndexBase_t idxBase, cudaDataType valueType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCreateCooAoS)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCreateCooAoS = (cusparseStatus_t (*)(cusparseSpMatDescr_t *, int64_t, int64_t, int64_t, void *, void *, cusparseIndexType_t, cusparseIndexBase_t, cudaDataType)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCreateCooAoS");
			fprintf(stderr, "wrapper_cusparseCreateCooAoS:%p\n", wrapper_cusparseCreateCooAoS);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCreateCooAoS():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCreateCooAoS(spMatDescr, rows, cols, nnz, cooInd, cooValues, cooIdxType, idxBase, valueType);
		return retval;
	}
}