#ifndef _OUROBOROS_PLUGIN_MANAGER_H_
#define _OUROBOROS_PLUGIN_MANAGER_H_

#include <server/ouroboros_server.h>
#include <map>
#include <string>

namespace ouroboros
{
	class plugin_manager
	{
	public:
		
		/**	Constructor. Uses a default directory for searching for plugins.
		 *	FIXME what's a reasonable default?
		 *	@param [in] aServer Server reference to pass to plugins.
		 *
		 */
		plugin_manager(ouroboros_server& aServer);
		
		/**	Destructor.
		 * 
		 */
		~plugin_manager();
		
		/**	Loads the given plugin.
		 *
		 *	@param [in] Path to the plugin to load, relative from the plugin
		 *		directory.
		 *
		 *	@returns True if the plugin loaded, false otherwise.
		 *
		 */
		bool load(const std::string& aPath);
		
		/**	Loads the given directory
		 * 
		 */
		std::size_t load_directory(const std::string& aDirectory);
		
		/**	Unloads the given plugin.
		 * 
		 *	@param [in] Path to the plugin to unload, relative from the plugin
		 *		directory.
		 *
		 *	@returns True if the plugin unloaded, false otherwise.
		 * 
		 */
		bool unload(const std::string& aPath);
		
	private:
		ouroboros_server& mServer;
		std::map<std::string, void*> mPlugins;
	};
}

#endif//_OUROBOROS_PLUGIN_MANAGER_H_
