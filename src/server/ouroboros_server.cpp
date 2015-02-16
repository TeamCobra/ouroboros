#include "ouroboros_server.h"
#include <server/data/data_store.hpp>
#include <server/device_tree.hpp>
#include <mongoose/mongoose.h>
#include <server/rest.h>

namespace ouroboros
{
	
	namespace detail
	{
		std::string bad_JSON()
		{
			return std::string("{ \"status\" : \"Bad JSON request.\"}");
		}
		
		std::string good_JSON()
		{
			return std::string("{ \"status\" : \"OK.\"}");
		}
	}
	
	mg_result ouroboros_server::handle_uri(mg_connection *conn, const std::string& uri)
	{
		rest_request request(conn, uri);
		if (request.getRestRequestType() != rest_request_type::NONE)
		{
			std::string output;
			
			return handle_rest(request);
		}
		return MG_FALSE;
	}

	int ouroboros_server::event_handler(mg_connection *conn, mg_event ev)
	{
		ouroboros_server *this_server = reinterpret_cast<ouroboros_server*>(conn->server_param);
		if (ev == MG_AUTH)
		{
			return MG_TRUE;
		}
		else if (ev == MG_REQUEST)
		{
			return this_server->handle_uri(conn, conn->uri);
		}
		else
		{
			return MG_FALSE;
		}
	}


	void *ouroboros_server::run_server(void *aThis)
	{
		ouroboros_server *this_server = reinterpret_cast<ouroboros_server*>(aThis);
		this_server->mpServer = mg_create_server(aThis, ouroboros_server::event_handler);
		mg_set_option(this_server->mpServer, "document_root", ".");      // Serve current directory
		mg_set_option(this_server->mpServer, "listening_port", "8080");  // Open port 8080

		while (this_server->mStarted)
		{
			mg_poll_server(this_server->mpServer, 1000);   // Infinite loop, Ctrl-C to stop
		}
		mg_destroy_server(&this_server->mpServer);
	
		return NULL;
	}
	
	ouroboros_server::ouroboros_server()
	:mStarted(false), mpServer(NULL),
		mStore(device_tree<var_field>::get_device_tree().get_data_store())
	{
		
		
		
	}
	
	ouroboros_server::~ouroboros_server()
	{
		
	}
	
	var_field *ouroboros_server::get(const std::string& aGroup, const std::string& aField)
	{
		return mStore.get(aGroup, aField);;
	}
	
	group<var_field> *ouroboros_server::get(const std::string& aGroup)
	{
		return mStore.get(aGroup);
	}
		
	void ouroboros_server::set(const std::string& aGroup, const std::string& aField, const var_field& aFieldData)
	{
		var_field *result = mStore.get(aGroup, aField);
		if (!result)
		{
			return; //FIXME maybe return an error?
		}
		*result = aFieldData;
	}
	
	void ouroboros_server::set(const std::string& aGroup, const group<var_field>& aField)
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
	
	mg_result ouroboros_server::handle_rest(const rest_request& aRequest)
	{
		switch (aRequest.getRestRequestType())
		{
			case rest_request_type::FIELDS:
				handle_name_rest(aRequest);
				break;
				
			case rest_request_type::GROUPS:
				handle_group_rest(aRequest);
				break;
				
			case rest_request_type::CUSTOM:
				handle_custom_rest(aRequest);
				break;
				
			case rest_request_type::NONE:
				break;
			default:
				return MG_FALSE;
		}
		return MG_TRUE;
	}
	
	void ouroboros_server::handle_name_rest(const rest_request& aRequest)
	{
		//get reference to named thing
		var_field *named = mStore.get(aRequest.getGroups(), aRequest.getFields());
		
		std::string sjson;
		mg_connection *conn = aRequest.getConnection();
		if (named)
		{
			switch (aRequest.getHttpRequestType())
			{
				case http_request_type::PUT:	
				{	
					std::string data(conn->content, conn->content_len);
					JSON json(data);
					
					if (named->setJSON(json))
					{
						sjson = detail::good_JSON();
					}
					else
					{
						sjson = detail::bad_JSON();
					}
				}
					break;
				
				case http_request_type::GET:
					//Send JSON describing named item
					sjson = named->getJSON();
					break;
				
				default:
					sjson = detail::bad_JSON();
			}
		}
		else
		{
			sjson = detail::bad_JSON();
		}
		
		mg_send_data(conn, sjson.c_str(), sjson.length());
	}

	void ouroboros_server::handle_group_rest(const rest_request& aRequest)
	{
		//get reference to named thing
		group<var_field> *pgroup = mStore.get(aRequest.getGroups());
		
		std::string sjson;
		if (pgroup)
		{
			switch (aRequest.getHttpRequestType())
			{
				case http_request_type::GET:
					//Send JSON describing named item
					sjson = pgroup->getJSON();
					break;
				
				default:
					sjson = detail::bad_JSON();
			}
		}
		else
		{
			sjson = detail::bad_JSON();
		}
		
		mg_connection *conn = aRequest.getConnection();
		mg_send_data(conn, sjson.c_str(), sjson.length());
	}

	void ouroboros_server::handle_custom_rest(const rest_request& aRequest)
	{
		//TODO Implement this somehow
	}
	
	std::string ouroboros_server::normalize_group(const std::string& aGroup)
	{
		std::string result = "server";
		if(!aGroup.empty())
		{
			result += "-" + aGroup;
		}
		
		return result;
	}
	
	/*template <typename Func>
	void ouroboros_server::register_callback(const std::string& aGroup, const std::string& aField, Func aCallback)
	{
		var_field *named = mStore.get(aGroup, aField);
		if (named)
		{
			callback<Func> cb(aGroup, aField, aCallback);
			mFieldCallbacks.push_back(cb);
			named->registerObserver(mFieldCallbacks.back());
		}
	}*/
	
}
