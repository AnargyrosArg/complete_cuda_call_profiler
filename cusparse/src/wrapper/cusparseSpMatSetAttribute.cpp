#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusparseStatus_t wrapper_cusparseSpMatSetAttribute(cusparseSpMatDescr_t spMatDescr, cusparseSpMatAttribute_t attribute, void *data, size_t dataSize)
{
	cusparseStatus_t retval = cusparseSpMatSetAttribute(spMatDescr, attribute, data, dataSize);
	return retval;
}