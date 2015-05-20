#ifndef _OUROBOROS_PLUGIN_H_
#define _OUROBOROS_PLUGIN_H_

#include <ouroboros/ouroboros_server.h>

namespace ouroboros
{
	//Defines the type of function that plugins must support.
	typedef bool (*plugin_entry_function)(ouroboros_server& aServer);

	/**	Function called by a plugin manager upon loading the plugin.
	 *
	 *	This function is called by a plugin manager upon finding and loading the
	 *	plugin. Plugin designers are free to execute any code they wish in this
	 *	function, but be advised that it is likely that blocking in this
	 *	function will make the entire program hang. As a result, it is advised
	 *	to make the code that executes here simple, and if necessary, spawn
	 *	external threads to do continuous and/or heavy work.
	 *
	 *	@param [in] aServer A reference to the server object passed in by the
	 *		plugin manager. All public methods defined by the server are
	 *		accessible.
	 *
	 *	@returns True upon success, false upon failure.
	 */
	extern "C" bool plugin_entry(ouroboros_server& aServer);

	//TODO implement an unload function
}

#endif//_OUROBOROS_PLUGIN_H_
