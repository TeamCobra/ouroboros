<% require './ranges' %>
<% define 'Tree', :for => this do %>
	#include <ouroboros/device_tree.tpp>
	#include <ouroboros/function_manager.h>

	#include <ouroboros/data/base.hpp>
	#include <ouroboros/data/base_string.h>
	#include <ouroboros/data/base_enum.h>
	#include <ouroboros/data/base_boolean.h>
	#include <ouroboros/data/base_number.hpp>
	#include <ouroboros/data/base_floating.hpp>
	#include <ouroboros/data/base_function.h>

	#include <stdint.h>
	#include <string>
	#include <cmath>

	<%nl%>
	namespace ouroboros
	{<%iinc%>
		namespace detail
		{<%iinc%>
			template<>
			group<var_field> build_tree(function_manager& aManager)
			{<%iinc%>	
				std::vector<std::string> params;
				group<var_field> result("server", "Root node.");
				std::map<std::string, int> enumMap;
				<%
					this.eContents.each do |item|
						if item.class.to_s === ServerModel::Field.to_s
							expand 'Field', :for => item
						elsif item.class.to_s === ServerModel::Group.to_s
							expand 'Group', :for => item
							expand 'AddGroup', :for => item
						end
					end
				%>
				<%nl%>
				return result;
			<%idec%>}
		<%idec%>}
	<%idec%>}
<% end %>

<% define 'Field', :for => this do %>
	<%if type == "functionField"%>
		params.clear();
	<%
	params[0].param.each {
		|x|
		%>
		params.push_back("<%= x.chardata[0].strip %>");
		<%
	}

	end
		
		if parent.class.to_s === ServerModel::DeviceConfig.to_s  
			parentGroupVar = 'result'
			operator = '.'
		else
			parentGroupVar = parent.title.chardata[0].strip.downcase.delete(' ')
			operator = '->'
		end
		
		if type == 'enumField'
			expand 'enumField::PrepareEnums', :for => this
		end
	%>
	<%= parentGroupVar %><%= operator %>add(new <%nonl%><%nows%>
	<%
		if type =~ /(un)?signed(Int|Short|Byte)Field/
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
		elsif type == "functionField"
			expand 'functionField::Field', :for => this
		end
	%>
	);
<% end %>

<% define 'Group', :for => this do %>
	<% groupVar = title.chardata[0].strip.downcase.delete(' ') %>
	group<var_field> *<%= groupVar %> = new group<var_field>("<%= title.chardata[0].strip %>", "<%= description.chardata[0].strip %>");	
	<%
		this.eContents.each do |item|
			if item.class.to_s === ServerModel::Field.to_s
				expand 'Field', :for => item
			elsif item.class.to_s === ServerModel::Group.to_s
				expand 'Group', :for => item
				expand 'AddGroup', :for => item
			end
		end
	%>
<% end %>

<% define 'AddGroup', :for => this do %>
	<% groupVar = title.chardata[0].strip.downcase.delete(' ') %>
	<% if parent.class.to_s != ServerModel::DeviceConfig.to_s %>
		<%= parent.title.chardata[0].strip.downcase.delete(' ') %>->add(<%= groupVar %>);
	<% else %>
		result.add(<%= groupVar %>);
	<% end %>
<% end %>

<% define 'AddParameters', :for => this do %>
	<% groupVar = title.chardata[0].strip.downcase.delete(' ') %>
	<% if parent.class.to_s != ServerModel::DeviceConfig.to_s %>
		<%= parent.title.chardata[0].strip.downcase.delete(' ') %>->add(<%= groupVar %>);
	<% else %>
		result.add(<%= groupVar %>);
	<% end %>
<% end %>
