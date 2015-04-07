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
			
			# set the bit size of the integer based on type
			case type 
			when /Int/ then this.Type = "int32_t"
			when /Short/ then this.Type = "int16_t"
			when /Byte/ then this.Type = "int8_t"
			end

			# if it is unsigned make it a uint
			this.Type.prepend "u" if this.Type =~ /unsigned/
			
			# set min and max based on predefined constants
			this.Min = Object.const_get("#{type}_MIN".upcase)
			this.Max = Object.const_get("#{type}_MAX".upcase)

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
