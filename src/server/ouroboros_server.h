#ifndef _OUROBOROS_OUROBOROS_SERVER_
#define _OUROBOROS_OUROBOROS_SERVER_

#include <server/data/base.hpp>
#include <server/data/data_store.hpp>
#include <pthread.h>
#include <mongoose/mongoose.h>
#include <server/rest.h>
#include <server/callback.hpp>
#include <server/data/subject.hpp>
#include <server/function_manager.h>

namespace ouroboros
{
	class ouroboros_server
	{
	public:
		typedef function_manager::function_f function_f;
		typedef void (*callback_f)(var_field* aField);
		
		
		/**	Constructor.
		 * 
		 *	Prepares server to run.
		 * 
		 */
		ouroboros_server();
		
		/**	Destructor.
		 *
		 *	Unloads server resources.
		 */
		~ouroboros_server();
		
		/**	Executes one iteration of the server's main routine.
		 * 
		 *	This function should be called in a loop in some thread, like main.
		 *	Each execution of the function causes the server to process its
		 *	currently pending I/O requests. One way to use this function is to
		 *	place it in the main function inside of a while loop with a
		 *	signal variable controlling when to exit.
		 *
		 *	@post The server has executed all I/O requests that were pending
		 *		previously.
		 */
		void run();
		
		//@{
		/**	Returns a pointer to an element stored within the server's device
		 *		tree structure.
		 *
		 *	@param [in] aGroup String describing the group of the desired
		 *		element.
		 *	@param [in] aField String describing the name of the desired field.
		 *
		 *	@returns A pointer to the desired element if found, NULL otherwise.
		 *
		 */
		var_field *get(const std::string& aGroup, const std::string& aField);
		const var_field *get(const std::string& aGroup, const std::string& aField) const;
		//@}
		
		//@{
		/**	Returns a pointer to a group structure stored within the server's
		 *		device tree structure.
		 *
		 *	@param [in] aGroup String describing the group of the desired
		 *		element.
		 *
		 *	@returns A pointer to the desired group if found, NULL otherwise.
		 *
		 */
		group<var_field> *get(const std::string&);
		const group<var_field> *get(const std::string&) const;
		//@}
		
		/**	Sets the content of the desired element to a copy of the one
		 *		specified.
		 *FIXME I don't think this function is implemented correctly
		 */
		bool set(const std::string& aGroup, const std::string& aField, const var_field& aFieldData);
		
		//FIXME do we even want this function?
		bool set(const std::string& aGroup, const group<var_field>& aField);
		
		/**	Registers a callback function for the specified element.
		 *
		 *	@param [in] aGroup String describing the group of the desired
		 *		element.
		 *	@param [in] aField String describing the name of the desired field.
		 *	@param [in] aCallback Callback functor that is called as void()
		 *		function.
		 *	@returns True upon success, false otherwise.
		 */
		bool register_callback(const std::string& aGroup, const std::string& aField, callback_f aCallback);
		
		/**	Registers a response function for the specified function call.
		 *
		 *	@param [in] aFunctionName Name of the function to register.
		 *	@param [in] aResponse Callback functor that is called as
		 * 		void(std::vector<std::string>) function.
		 *	@returns True upon success, false otherwise.
		 */
		bool register_function(const std::string& aFunctionName, function_f aResponse);
		
		/**	Executes a response function for the specified function call.
		 *
		 *	@param [in] aFunctionName Name of the function to call.
		 *	@param [in] aParameters Parameters as strings in a vector.
		 */
		void execute_function(const std::string& aFunctionName, const std::vector<std::string>& aParameters);
		
	private:
		
		static const std::string group_delimiter;

		mg_result handle_uri(mg_connection *conn, const std::string& uri);
		mg_result handle_rest(const rest_request& request);
		void handle_name_rest(const rest_request& aRequest);
		void handle_group_rest(const rest_request& aRequest);
		void handle_custom_rest(const rest_request& aRequest);
		
		static int event_handler(mg_connection *conn, mg_event ev);
		static std::string normalize_group(const std::string& aGroup);
		
		//@{
		//Do not allow for the server to be copyable nor allow for it to be
		//assigned to anything else.
		ouroboros_server(const ouroboros_server&);
		ouroboros_server& operator=(const ouroboros_server&);
		//@}
		
		mg_server *mpServer;
		data_store<var_field>& mStore;
		
		std::map<std::string, callback<std::vector<std::string>, function_f> > mFunctionCallbacks;
		std::map<std::string, subject<callback<var_field*, callback_f> > > mCallbackSubjects;
		void handle_notification(const std::string& aGroup, const std::string& aField);
		
	};
}

#endif//_OUROBOROS_OUROBOROS_SERVER_
