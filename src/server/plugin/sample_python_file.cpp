#include <Python.h>
#include <server/plugin.h>
#include <cstdio>

static const char* script = "./plugin/sample_python.py";

extern "C" bool plugin_entry(ouroboros::ouroboros_server&)
{
	//Py_SetProgramName(name.c_str());  /* optional but recommended */
	Py_Initialize();
	FILE *file = fopen(script, "r");
	if (file)
	{
		PyRun_SimpleFile(file, script);
	}
	Py_Finalize();
	return true;
}

