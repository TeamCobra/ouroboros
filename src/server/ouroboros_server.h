#ifndef _OUROBOROS_OUROBOROS_SERVER_
#define _OUROBOROS_OUROBOROS_SERVER_

#include <server/data/base.hpp>
#include <server/data/data_store.hpp>
#include <pthread.h>
#include <mongoose/mongoose.h>
#include <server/rest.h>
#include <server/callback.h>

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
		
		void set(const std::string& aGroup, const std::string& aField, const var_field& aFieldData);
		void set(const std::string& aGroup, const group<var_field>& aField);
		
		template <typename Func>
		void register_callback(const std::string& aGroup, const std::string& aField, Func aCallback)
		{
			var_field *named = mStore.get(normalize_group(aGroup), aField);
			if (named)
			{
				callback<Func> cb(aGroup, aField, aCallback);
				mFieldCallbacks.push_back(cb);
				named->registerObserver(mFieldCallbacks.back());
			}
		}
		
		//Do something about callbacks?
		
	private:
		static void* run_server(void*);
		
		mg_result handle_uri(mg_connection *conn, const std::string& uri);
		static int event_handler(mg_connection *conn, mg_event ev);
		mg_result handle_rest(const rest_request& request);
		void handle_name_rest(const rest_request& aRequest);
		void handle_group_rest(const rest_request& aRequest);
		void handle_custom_rest(const rest_request& aRequest);
		static std::string normalize_group(const std::string& aGroup);
		
		ouroboros_server(const ouroboros_server&);
		ouroboros_server& operator=(const ouroboros_server&);
		
		bool mStarted;
		mg_server *mpServer;
		data_store<var_field>& mStore;
		
		pthread_t mThread;
		
		typedef void (*callback_function)(const std::string& aGroup, const std::string& aField);
		
		std::vector<callback<callback_function>> mFieldCallbacks;
		
	};
}

#endif//_OUROBOROS_OUROBOROS_SERVER_