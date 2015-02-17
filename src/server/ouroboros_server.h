#ifndef _OUROBOROS_OUROBOROS_SERVER_
#define _OUROBOROS_OUROBOROS_SERVER_

#include <server/data/base.hpp>
#include <server/data/data_store.hpp>
#include <pthread.h>
#include <mongoose/mongoose.h>
#include <server/rest.h>
#include <server/callback.h>
#include <server/data/observer.h>

namespace ouroboros
{
	class ouroboros_server
	{
	public:
		ouroboros_server();
		~ouroboros_server();
		
		void start();
		void stop();
		bool started();
		
		var_field *get(const std::string& aGroup, const std::string& aField);
		group<var_field> *get(const std::string&);
		
		bool set(const std::string& aGroup, const std::string& aField, const var_field& aFieldData);
		bool set(const std::string& aGroup, const group<var_field>& aField);
		
		template <typename Func>
		void register_callback(const std::string& aGroup, const std::string& aField, Func aCallback);
		
	private:
		static void* run_server(void*);
		
		mg_result handle_uri(mg_connection *conn, const std::string& uri);
		mg_result handle_rest(const rest_request& request);
		void handle_name_rest(const rest_request& aRequest);
		void handle_group_rest(const rest_request& aRequest);
		void handle_custom_rest(const rest_request& aRequest);
		
		static int event_handler(mg_connection *conn, mg_event ev);
		static std::string normalize_group(const std::string& aGroup);
		
		ouroboros_server(const ouroboros_server&);
		ouroboros_server& operator=(const ouroboros_server&);
		
		mg_server *mpServer;
		data_store<var_field>& mStore;
		
		bool mStarted;
		pthread_t mThread;
		
		typedef void (*callback_function)(const std::string& aGroup, const std::string& aField);
		std::map<std::string, subject<callback<callback_function> > > mCallbackSubjects;
		void handle_notification(const std::string& aGroup, const std::string& aField);
		
	};
}

#include <server/ouroboros_server.ipp>

#endif//_OUROBOROS_OUROBOROS_SERVER_