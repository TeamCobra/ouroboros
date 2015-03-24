require './ranges'

class LogicChecker
	NUM_TYPES = ["intField", "signedIntField", "unsignedIntField", "signedShortField",
		"unsignedShortField", "signedByteField", "unsignedByteField", "booleanField"]

	def checkLogic(model)
		model.field.each do |field|
			if NUM_TYPES.include? field.type
				checkNumFieldLogic(field, false)
			elsif field.type === "doubleField" or field.type === "floatField"
				checkNumFieldLogic(field, true)
			elsif field.type === "stringField"
				checkStringField(field)
			end
		end
		model.group.each do |group|
			checkLogic(group)
		end	
	end

	def checkNumFieldLogic(field, decimal)
		absoluteMin = Object.const_get(field.type.upcase + "_MIN")
		absoluteMax = Object.const_get(field.type.upcase + "_MAX")
		
		!decimal ? value = field.value.chardata[0].to_i : value = field.value.chardata[0].to_f
		
		if defined? field.min and not field.min.empty?
			!decimal ? min = field.min.chardata[0].strip.to_i : min = field.min.chardata[0].strip.to_f
			if min < absoluteMin or value < min
				puts "\nERROR: check min #{field.title.chardata[0].strip} value in XML"
				exit 1
			end
		else
			if value < absoluteMin
				puts "\nERROR: check min #{field.title.chardata[0].strip} value in XML"
				exit 1
			end
		end
		
		if defined? field.max and not field.max.empty?
			!decimal ? max = field.max.chardata[0].strip.to_i : max = field.max.chardata[0].strip.to_f 
			if max > absoluteMax or value > max
				puts "\nERROR: check max #{field.title.chardata[0].strip} value in XML"
				exit 1
			end
		else
			if value > absoluteMax
				puts "\nERROR: check max #{field.title.chardata[0].strip} value in XML"
				exit 1
			end
		end
	end

	def checkStringField(field)
		value = field.value.chardata[0].strip
		if defined? field.minLength and not field.minLength.empty?
			minLength = field.min.chardata[0].strip.to_i
			if value.length < minLength
				puts "\nERROR: check minLength #{field.title.chardata[0].strip} value in XML"
				exit 1
			end
		end

		if defined? field.maxLength and not field.maxLength.empty?
			maxLength = field.max.chardata[0].strip.to_i
			if value.length < maxLength
				puts "\nERROR: check maxLength #{field.title.chardata[0].strip} value in XML"
				exit 1
			end
		end

		if defined? field.pattern and not field.pattern.empty?
			if not value =~ /#{field.pattern.chardata[0].strip}/
				puts "\nERROR: check regex pattern for #{field.title.chardata[0].strip} string in XML"
			end
		end
	end
end
