<% require './ranges' %>
<% define 'Tree', :for => this do %>
	#include <server/device_tree.tpp>
	#include <data/base.hpp>
	#include <data/base_string.h>
	#include <data/base_number.hpp>
	#include <data/base_boolean.h>
	#include <data/base_floating.hpp>
	#include <stdint.h>
	#include <string>
	#include <cmath>
	
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
				attr_accessor :Type;
				attr_accessor :Min;
				attr_accessor :Max;
			end
			if type === "signedIntField"
				this.Type = "int32_t"
				this.Min = SIGNEDINTFIELD_MIN
				this.Max = SIGNEDINTFIELD_MAX
			elsif type === "unsignedIntField"
				this.Type = "uint32_t"
				this.Min = UNSIGNEDINTFIELD_MIN
				this.Max = UNSIGNEDINTFIELD_MAX
			elsif type === "signedShortField"
				this.Type = "int16_t"
				this.Min = SIGNEDSHORTFIELD_MIN
				this.Max = SIGNEDSHORTFIELD_MAX
			elsif type === "unsignedShortField"
				this.Type = "uint16_t"
				this.Min = UNSIGNEDSHORTFIELD_MIN
				this.Max = UNSIGNEDSHORTFIELD_MAX
			elsif type === "signedByteField"
				this.Type = "int8_t"
				this.Min = SIGNEDBYTEFIELD_MIN
				this.Max = SIGNEDBYTEFIELD_MAX
			elsif type === "unsignedByteField"
				this.Type = "uint8_t"
				this.Min = UNSIGNEDBYTEFIELD_MIN
				this.Max = UNSIGNEDBYTEFIELD_MAX
			end
			expand 'numberField::Field', :for => this 
			
		elsif type === "stringField"
			expand 'stringField::Field', :for => this
		elsif type =~ /(double|float)Field/
			class << this
				attr_accessor :Type;
				attr_accessor :Min;
				attr_accessor :Max;
			end
			
			if type === "doubleField"	
				this.Type = "double"
				this.Min = DOUBLEFIELD_MIN
				this.Max = DOUBLEFIELD_MAX
			elsif type === "floatField"
				this.Type = "float"
				this.Min = FLOATFIELD_MIN
				this.Max = FLOATFIELD_MAX
			end
			expand 'floatingField::Field', :for => this
			
		elsif type == "enumField"
			expand 'enumField::Field', :for => this
		elsif type === "booleanField"
			expand 'booleanField::Field', :for => this
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
