#ifndef _OUROBOROS_OUROBOROS_SERVER_
#define _OUROBOROS_OUROBOROS_SERVER_

#include <server/data/base.hpp>
#include <server/data/data_store.hpp>
#include <server/device_tree.hpp>
#include <pthread.h>
#include <mongoose/mongoose.h>
#include <server/rest.h>

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
		
		var_field *get(const char* aGroup, const char* aField);
		group<var_field> *get(const char*);
		
		void set(const char* aGroup, const char* aField, const var_field& aFieldData);
		void set(const char*, const group<var_field>& aField);
		
		//Do something about callbacks?
		
	private:
		static void* run_server(void*);
		
		mg_result handle_uri(mg_connection *conn, const char* uri);
		static int event_handler(mg_connection *conn, mg_event ev);
		mg_result handle_rest(const rest_request& request);
		void handle_name_rest(const rest_request& aRequest);
		void handle_group_rest(const rest_request& aRequest);
		void handle_custom_rest(const rest_request& aRequest);
		
		ouroboros_server(const ouroboros_server&);
		ouroboros_server& operator=(const ouroboros_server&);
		
		bool mStarted;
		mg_server *mpServer;
		data_store<var_field>& mStore;
		
		pthread_t mThread;
		
	};
}

#endif//_OUROBOROS_OUROBOROS_SERVER_