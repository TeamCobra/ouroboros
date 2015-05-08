#include "ouroboros_server.h"
#include <server/data/data_store.hpp>
#include <server/device_tree.hpp>
#include <mongoose/mongoose.h>
#include <server/rest.h>
#include <sstream>

namespace ouroboros
{	
	namespace detail
	{
		std::string bad_JSON(mg_connection* aConn)
		{
			mg_send_status(aConn, 400);
			return std::string("{ \"status\" : \"Bad JSON request.\"}");
		}
		
		std::string good_JSON()
		{
			return std::string("{ \"status\" : \"OK.\"}");
		}
	}
	
	ouroboros_server::ouroboros_server()
	:mpServer(NULL),
		mStore(device_tree<var_field>::get_device_tree().get_data_store())
	{
		mpServer = mg_create_server(this, ouroboros_server::event_handler);
		mg_set_option(mpServer, "document_root", ".");      // Serve current directory
		mg_set_option(mpServer, "listening_port", "8080");  // Open port 8080
	}
	
	ouroboros_server::~ouroboros_server()
	{
		mg_destroy_server(&mpServer);
	}
	
	const var_field *ouroboros_server::get(const std::string& aGroup, const std::string& aField) const
	{
		return mStore.get(normalize_group(aGroup), aField);
	}
	
	var_field *ouroboros_server::get(const std::string& aGroup, const std::string& aField)
	{
		return const_cast<var_field *>(static_cast<const ouroboros_server&>(*this).get(aGroup, aField));
	}
	
	const group<var_field> *ouroboros_server::get(const std::string& aGroup) const
	{
		return mStore.get(normalize_group(aGroup));
	}
	
	group<var_field> *ouroboros_server::get(const std::string& aGroup)
	{
		return const_cast<group<var_field> *>(static_cast<const ouroboros_server&>(*this).get(aGroup));
	}
		
	bool ouroboros_server::set(const std::string& aGroup, const std::string& aField, const var_field& aFieldData)
	{
		var_field *result = mStore.get(normalize_group(aGroup), aField);
		if (!result)
		{
			return false;
		}
		result->setJSON(aFieldData.getJSON());

		handle_notification(aGroup, aField);
		return true;
	}
	
	bool ouroboros_server::set(const std::string& , const group<var_field>& )
	{
		return false;
	}
	
	void ouroboros_server::run()
	{
		mg_poll_server(mpServer, 1000);
	}
		
	mg_result ouroboros_server::handle_rest(const rest_request& aRequest)
	{
		switch (aRequest.getRestRequestType())
		{
			case FIELDS:
				handle_name_rest(aRequest);
				break;
				
			case GROUPS:
				handle_group_rest(aRequest);
				break;
				
			case CALLBACK:
				handle_callback_rest(aRequest);
				break;
				
			case NONE:
				break;
			default:
				return MG_FALSE;
		}
		return MG_TRUE;
	}
	
	void ouroboros_server::handle_name_rest(const rest_request& aRequest)
	{
		//get reference to named thing
		var_field *named = mStore.get(normalize_group(aRequest.getGroups()), aRequest.getFields());
		
		std::string sjson;
		mg_connection *conn = aRequest.getConnection();
		if (named)
		{
			switch (aRequest.getHttpRequestType())
			{
				case PUT:	
				{	
					std::string data(conn->content, conn->content_len);
					JSON json(data);
					
					if (named->setJSON(json))
					{
						handle_notification(aRequest.getGroups(), aRequest.getFields());
						sjson = detail::good_JSON();
					}
					else
					{
						sjson = detail::bad_JSON(conn);
					}
				}
					break;
				
				case GET:
					//Send JSON describing named item
					sjson = named->getJSON();
					break;
				
				default:
					sjson = detail::bad_JSON(conn);
			}
		}
		else
		{
			sjson = detail::bad_JSON(conn);
		}
		
		mg_send_data(conn, sjson.c_str(), sjson.length());
	}

	void ouroboros_server::handle_group_rest(const rest_request& aRequest)
	{
		//get reference to named thing
		group<var_field> *pgroup = mStore.get(normalize_group(aRequest.getGroups()));
		
		std::string sjson;
		mg_connection *conn = aRequest.getConnection();
		if (pgroup)
		{
			switch (aRequest.getHttpRequestType())
			{
				case GET:
					//Send JSON describing named item
					sjson = pgroup->getJSON();
					break;
				
				default:
					sjson = detail::bad_JSON(conn);
			}
		}
		else
		{
			sjson = detail::bad_JSON(conn);
		}
		
		mg_send_data(conn, sjson.c_str(), sjson.length());
	}

	void ouroboros_server::handle_callback_rest(const rest_request& aRequest)
	{
		//get reference to named thing
		std::string resource = normalize_group(aRequest.getGroups()) + '/' + aRequest.getFields();
		var_field *named = mStore.get(normalize_group(aRequest.getGroups()), aRequest.getFields());
		
		std::string response;
		mg_connection *conn = aRequest.getConnection();
		if (named)
		{
			switch (aRequest.getHttpRequestType())
			{
				case POST:
				{
					std::stringstream ss;
					ss << "{ \"id\" : ";
					mCallbackManager.register_callback(resource);
					
					std::string data(conn->content, conn->content_len);
					JSON json(data);

				}
					break;

				case DELETE:
					//Send JSON describing named item
					response = named->getJSON();
					break;
				
				default:
					response = detail::bad_JSON(conn);
			}
		}
		else
		{
			response = detail::bad_JSON(conn);
		}

		mg_send_data(conn, response.c_str(), response.length());
	}
	
	std::string ouroboros_server::normalize_group(const std::string& aGroup)
	{
		std::string result = "server";
		if(!aGroup.empty())
		{
			result += group_delimiter + aGroup;
		}
		
		return result;
	}
	
	void ouroboros_server::handle_notification(const std::string& aGroup, const std::string& aField)
	{
		std::string key(aGroup+'/'+aField);
		if (mCallbackSubjects.count(key))
		{
			mCallbackSubjects[key].notify();
		}
	}
	
	mg_result ouroboros_server::handle_uri(mg_connection *conn, const std::string& uri)
	{
		rest_request request(conn, uri);
		if (request.getRestRequestType() != NONE)
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
	
	std::string ouroboros_server::register_callback(const std::string& aGroup, const std::string& aField, callback_function aCallback)
	{
		std::string result;
		var_field *named = mStore.get(normalize_group(aGroup), aField);
		if (named)
		{
			std::string key(aGroup+"/"+aField);
			result = key;
			if (!mCallbackSubjects.count(key))
			{
				mCallbackSubjects[key] = subject<id_callback<var_field*, callback_function> >();
			}
			
			id_callback<var_field*, callback_function> cb(result, named, aCallback);
			mCallbackSubjects[key].registerObserver(cb);
		}
		return result;
	}

	const std::string ouroboros_server::group_delimiter(data_store<var_field>::group_delimiter);
}
