#ifndef _OUROBOROS_OUROBOROS_SERVER_
#define _OUROBOROS_OUROBOROS_SERVER_

#include <ouroboros/rest.h>
#include <ouroboros/callback.hpp>
#include <ouroboros/callback_manager.h>
#include <ouroboros/data/base.hpp>
#include <ouroboros/data/data_store.hpp>
#include <ouroboros/data/subject.hpp>
#include <ouroboros/function_manager.h>
#include <ouroboros/device_tree.hpp>

#include <pthread.h>
#include <mongoose/mongoose.h>


//This header is not in C++03, but it can be found online if the platform does
//not already support C99. Most modern Linux systems have stdint.h in their
//include folders, so it should be picked up automatically.
#include <stdint.h>

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
		 *	@param [in] aPort Port to listen on.
		 *
		 */
		ouroboros_server(uint16_t aPort);

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
		const var_field *get(
			const std::string& aGroup, const std::string& aField) const;
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
		 */
		bool set(
			const std::string& aGroup,
			const std::string& aField,
			const var_field& aFieldData);

		/**	Registers a callback function for the specified element.
		 *
		 *	@param [in] aGroup String describing the group of the desired
		 *		element.
		 *	@param [in] aField String describing the name of the desired field.
		 *	@param [in] aCallback Callback functor that is called as void()
		 *		function.
		 *	@returns The string ID for the callback, or an empty string if it
		 *		failed.
		 *
		 */
		std::string register_callback(
			const std::string& aGroup,
			const std::string& aField,
			callback_f aCallback);

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

		/**	Unregisters a callback function for the specified element.
		 *
		 *	@param [in] aID String describing the ID of the callback.
		 *
		 */
		void unregister_callback(const std::string& aID);

	private:

		static const std::string group_delimiter;

		mg_result handle_uri(mg_connection *conn, const std::string& uri);
		mg_result handle_rest(const rest_request& request);
		void handle_name_rest(const rest_request& aRequest);
		void handle_group_rest(const rest_request& aRequest);
		void handle_callback_rest(const rest_request& aRequest);

		void handle_function_rest(const rest_request& aRequest);
		void handle_notification(
			const std::string& aGroup, const std::string& aField);

		static ouroboros_server *mpSendServer;
		static void establish_connection(var_field* aResponse);
		void send_response(mg_connection* aConn);

		static int event_handler(mg_connection *conn, mg_event ev);
		static std::string normalize_group(const std::string& aGroup);

		//@{
		//Do not allow for the server to be copyable nor allow for it to be
		//assigned to anything else.
		ouroboros_server(const ouroboros_server&);
		ouroboros_server& operator=(const ouroboros_server&);
		//@}

		mg_server *mpServer;
		device_tree<var_field> mTree;
		data_store<var_field>& mStore;

		function_manager &mFunctionManager;

		callback_manager mCallbackManager;
		std::map<std::string, subject<
				id_callback<var_field*, callback_f> > > mCallbackSubjects;

		std::map<var_field *, std::string> mResponseUrls;
	};
}

#endif//_OUROBOROS_OUROBOROS_SERVER_

