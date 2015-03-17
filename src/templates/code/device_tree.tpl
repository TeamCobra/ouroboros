<% define 'Tree', :for => this do %>
	#include <server/device_tree.tpp>
	#include <data/base.hpp>
	#include <data/base_string.h>
	#include <data/base_number.hpp>
	#include <string>
	#include <limits>
	<%nl%>
	namespace ouroboros
	{<%iinc%>
		namespace detail
		{<%iinc%>
			template<>
			group<var_field> build_tree()
			{<%iinc%>		
				group<var_field> result("server", "Root node.");
				<% 
					expand 'Field', :foreach => field
					expand 'Group', :foreach => group
					expand 'AddGroup', :foreach => group
				%>
				<%nl%>
				return result;
			<%idec%>}
		<%idec%>}
	<%idec%>}
<% end %>

<% define 'Field', :for => this do %>
	<%
		if parent.class.to_s === ServerModel::DeviceConfig.to_s  
			parentGroupVar = 'result'
			operator = '.'
		
		else
			parentGroupVar = parent.title.chardata[0].strip.downcase.delete(' ')
			operator = '->'
		end
	%>
	<%= parentGroupVar %><%= operator %>add(new <%nonl%><%nows%>
	<%
		if type =~ /(un)?signed(Int|Short|Byte)Field/ or type === "intField"
			class << this
				attr_accessor :Min;
				attr_accessor :Max;
			end
			if type === "intField" or type === "signedIntField"
				this.Min = -2147483648
				this.Max = 2147483647
			elsif type === "unsignedIntField"
				this.Min = 0
				this.Max = 4294967295
			elsif type === "signedShortField"
				this.Min = -32768
				this.Max = 32767
			elsif type === "unsignedShortField"
				this.Min = 0
				this.Max = 65535
			elsif type === "signedByteField"
				this.Min = -128
				this.Max = 127
			elsif type === "unsignedByteField"
				this.Min = 0
				this.Max = 255
			end
			
			expand 'numberField::Field', :for => this 
			
		elsif type === "stringField"
			expand 'stringField::Field', :for => this
		elsif type == "doubleField"
			expand 'doubleField::Field', :for => this
		elsif type == "floatField"
			expand 'floatField::Field', :for => this
		elsif type == "enumField"
			expand 'enumField::Field', :for => this
		end
	%>
	);
<% end %>


<% define 'Group', :for => this do %>
	<% groupVar = title.chardata[0].strip.downcase.delete(' ') %>
	group<var_field> *<%= groupVar %> = new group<var_field>("<%= title.chardata[0].strip %>", "<%= description.chardata[0].strip %>");	
	<% expand 'Field', :foreach => field %>
	<% expand 'Group', :foreach => group %>
	<% expand 'AddGroup', :foreach => group %>
<% end %>

<% define 'AddGroup', :for => this do %>
	<% groupVar = title.chardata[0].strip.downcase.delete(' ') %>
	<% if parent.class.to_s != ServerModel::DeviceConfig.to_s %>
		<%= parent.title.chardata[0].strip.downcase.delete(' ') %>->add(<%= groupVar %>);
	<% else %>
		result.add(<%= groupVar %>);
	<% end %>
<% end %>


