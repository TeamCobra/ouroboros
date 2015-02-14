#include "ouroboros_server.h"
#include <server/data/data_store.hpp>
#include <server/device_tree.hpp>
#include <mongoose/mongoose.h>
#include <server/rest.h>
#include <server/rest_handlers.h>

namespace ouroboros
{
	namespace detail
	{
		enum mg_result handle_uri(struct mg_connection *conn, const char* uri)
		{
			if (get_REST_call_type(uri) != REST_call_type::NONE)
			{
				std::string output;

				switch (get_REST_call_type(uri))
				{
					case REST_call_type::NAME:
						handle_name_REST(conn, uri);
						break;
						
					case REST_call_type::GROUP:
						handle_group_REST(conn, uri);
						break;
					
					case REST_call_type::CUSTOM:
						handle_custom_REST(conn, uri);
						break;
					
					default:
						return MG_FALSE; //Something really bad just took place... We got a REST call type that wasn't NONE but we didn't recognize!
				}
				return MG_TRUE;
			}
			return MG_FALSE;
		}

		int event_handler(struct mg_connection *conn, enum mg_event ev)
		{
			if (ev == MG_AUTH)
			{
				return MG_TRUE;
			}
			else if (ev == MG_REQUEST)
			{
				return handle_uri(conn, conn->uri);
			}
			else
			{
				return MG_FALSE;
			}
		}
	}

	void *ouroboros_server::run_server(void *aThis)
	{
		ouroboros_server *this_server = reinterpret_cast<ouroboros_server*>(aThis);
		struct mg_server *server = mg_create_server(NULL, detail::event_handler);
		mg_set_option(server, "document_root", ".");      // Serve current directory
		mg_set_option(server, "listening_port", "8080");  // Open port 8080

		while (this_server->mStarted)
		{
			mg_poll_server(server, 1000);   // Infinite loop, Ctrl-C to stop
		}
		mg_destroy_server(&server);
	
		return NULL;
	}
	
	ouroboros_server::ouroboros_server()
	:mStarted(false), mTree(device_tree<var_field>::get_device_tree()),
		mStore(mTree.get_data_store())
	{
		
		
		
	}
	
	ouroboros_server::~ouroboros_server()
	{
		
	}
	
	var_field *ouroboros_server::get(const char* aGroup, const char* aField)
	{
		return mStore.get(aGroup, aField);;
	}
	
	group<var_field> *ouroboros_server::get(const char* aGroup)
	{
		return mStore.get(aGroup);
	}
		
	void ouroboros_server::set(const char* aGroup, const char* aField, const var_field& aFieldData)
	{
		var_field *result = mStore.get(aGroup, aField);
		if (!result)
		{
			return; //FIXME maybe return an error?
		}
		*result = aFieldData;
	}
	
	void ouroboros_server::set(const char* aGroup, const group<var_field>& aField)
	{
		
	}
	
	void ouroboros_server::start()
	{
		if (!mStarted)
		{
			mStarted = true;
			pthread_create(&mThread, NULL, run_server, this); //FIXME check return code
		}
	}
	
	void ouroboros_server::stop()
	{
		mStarted = false;
		pthread_join(mThread, NULL);
	}
	
	bool ouroboros_server::started()
	{
		return false;
	}
	
}