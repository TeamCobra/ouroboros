class Validator
	def validate(model)
		valid = true
		model.eAllContents.each do |item|
			if item.class.to_s === ServerModel::Field.to_s or item.class.to_s === ServerModel::Group.to_s	
				if not item.title.size === 1
					puts "\nERROR: Multiple or missing <title> tags for an element\n\n"
					exit 1	
				end
				
				if not item.description.size === 1
					puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
								"Concerning <description> tag\n"
					valid = false
				end
			end	

			if item.class.to_s === ServerModel::Field.to_s
				if not item.type === 'functionField'
					if item.value.size === 0
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"Missing <value> tag\n"
						valid = false
					end
				end

				if item.type === 'signedIntField' or item === 'unsignedIntField' or
						item.type === 'signedByteField' or item.type === 'unsignedByteField' or
						item.type === 'signedShortField' or item.type === 'unsignedShortField' or
						item.type === 'floatField' or item.type === 'doubleField'
						
					if item.min.size > 1
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"Multiple <min> tags defined\n"
						valid = false
					end				
					if item.max.size > 1
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"Multiple <max> tags defined\n"
						valid = false 
					end
					if item.value.size > 1
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"Multiple <value> tags defined\n"
						valid = false 
					end
					if item.minLength.size > 0
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"<minLength> tag cannot be not used for type enumField\n"
						valid = false
					end				
					if item.maxLength.size > 0
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"<maxLength> tag cannot be not used for type enumField\n"
						valid = false 
					end
					if item.pattern.size > 0
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"<pattern> tag cannot be not used for type enumField\n"
						valid = false
					end	
					
				elsif item.type === 'stringField'
					if item.minLength.size > 1
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"Multiple <minLength> tags defined\n"
						valid = false
					end				
					if item.maxLength.size > 1
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"Multiple <maxLength> tags defined\n"
						valid = false 
					end
					if item.value.size > 1
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"Multiple <value> tags defined\n"
						valid = false 
					end				
					if item.min.size > 0
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"<min> tag cannot be not used for type stringField\n"
						valid = false
					end				
					if item.max.size > 0
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"<max> tag cannot be not used for type stringField\n"
						valid = false 
					end

				elsif item.type === 'enumField' or item.type === 'booleanField' or item.type === 'functionField'
					if item.type === 'functionField'
						if item.params.size === 0
							puts "\nERROR in function field: #{item.title.chardata[0].strip}\n" +
									"No <params> tag defined\n"
							valid = false
						end
						if item.params.size > 1
							puts "\nERROR in function field: #{item.title.chardata[0].strip}\n" +
									"Multiple <params> tags defined\n"
							valid = false 
						end
					end

					if item.min.size > 0
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"<min> tag cannot be not used for type enumField\n"
						valid = false
					end				
					if item.max.size > 0
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"<max> tag cannot be not used for type enumField\n"
						valid = false 
					end
					if item.minLength.size > 0
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"<minLength> tag cannot be not used for type enumField\n"
						valid = false
					end				
					if item.maxLength.size > 0
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"<maxLength> tag cannot be not used for type enumField\n"
						valid = false 
					end
					if item.pattern.size > 0
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"<pattern> tag cannot be not used for type enumField\n"
						valid = false
					end				
				
				else
						puts "\nERROR in field: #{item.title.chardata[0].strip}\n" +
									"Invalid type: #{item.type}\n"
						valid = false
				end		
			end
		end
		return valid
	end	
end
