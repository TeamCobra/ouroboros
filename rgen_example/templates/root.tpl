<% define 'Root' do %>
	<% file 'hello.c' do %>
		<% expand 'code/hello::HelloWorld', :for => server %>
	<% end %>
<% end %>
