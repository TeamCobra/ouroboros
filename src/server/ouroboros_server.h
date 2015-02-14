#ifndef _OUROBOROS_OUROBOROS_SERVER_
#define _OUROBOROS_OUROBOROS_SERVER_

#include <server/data/base.hpp>
#include <server/data/data_store.hpp>
#include <server/device_tree.hpp>
#include <pthread.h>

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
		bool mStarted;
		static void* run_server(void*);
		
		ouroboros_server(const ouroboros_server&);
		ouroboros_server& operator=(const ouroboros_server&);
		
		device_tree<var_field>& mTree;
		data_store<var_field>& mStore;
		
		pthread_t mThread;
		
	};
}

#endif//_OUROBOROS_OUROBOROS_SERVER_