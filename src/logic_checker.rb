require './ranges'

class LogicChecker
	NUM_TYPES = ["intField", "signedIntField", "unsignedIntField", "signedShortField",
		"unsignedShortField", "signedByteField", "unsignedByteField", "booleanField"]
	
	@@logical = true

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
		return @@logical	
	end

	def checkNumFieldLogic(field, decimal)
		absoluteMin = Object.const_get(field.type.upcase + "_MIN")
		absoluteMax = Object.const_get(field.type.upcase + "_MAX")
		
		!decimal ? value = field.value.chardata[0].to_i : value = field.value.chardata[0].to_f
		
		if field.min.size > 0
			!decimal ? min = field.min.chardata[0].strip.to_i : min = field.min.chardata[0].strip.to_f
			if min < absoluteMin
				puts "\nERROR in field: #{field.title.chardata[0].strip}\n" +
							"min: #{min} is outside of range for data type #{field.type}\n" +
							"#{field.type} range: #{absoluteMin} - #{absoluteMax}\n"
				@@logical = false;
			end
			if value < min
				puts "\nERROR in field: #{field.title.chardata[0].strip}\n" +
							"value: #{value} is lower than the assigned min\n" +
							"min: #{min}\n"				
				@@logical = false;
			end
		else
			if value < absoluteMin
				puts "\nERROR in field: #{field.title.chardata[0].strip}\n" + 
							"value: #{value} is outside of range for data type #{field.type}\n" +
							"#{field.type} range: #{absoluteMin} - #{absoluteMax}\n"
				@@logical = false;
			end
		end
		
		if field.max.size > 0
			!decimal ? max = field.max.chardata[0].strip.to_i : max = field.max.chardata[0].strip.to_f 
			if max > absoluteMax
				puts "\nERROR in field: #{field.title.chardata[0].strip}\n" +
							"max: #{max} is outside of range for data type #{field.type}\n" +
							"#{field.type} range: #{absoluteMin} - #{absoluteMax}\n"
				@@logical = false
			end
			if value > max
				puts "\nERROR in field: #{field.title.chardata[0].strip}\n" +
							"value: #{value} is greater than the assigned max\n" +
							"max: #{max}\n"
				@@logical = false;
			end
		else
			if value > absoluteMax
				puts "\nERROR in field: #{field.title.chardata[0].strip}\n" +
							"value: #{value} is outside of range for data type #{field.type}\n" +
							"#{field.type} range: #{absoluteMin} - #{absoluteMax}\n"
				@@logical = false;
			end
		end
	end

	def checkStringField(field)
		value = field.value.chardata[0].strip
		if field.minLength.size > 0
			minLength = field.minLength.chardata[0].strip.to_i
			if value.length < minLength
				puts "\nERROR in field: #{field.title.chardata[0].strip}\n" +
							"value: \"#{value}\" length (#{value.length}) is lower than the assigned minlength\n" +
							"minLength: #{minLength}\n"
				@@logical = false
			end
		end

		if field.maxLength.size > 0
			maxLength = field.maxLength.chardata[0].strip.to_i
			if value.length > maxLength
				puts "\nERROR in field: #{field.title.chardata[0].strip}\n" +
							"value: \"#{value}\" length (#{value.length}) is greater than the assigned maxlength\n" +
							"maxLength: #{maxLength}\n"
				@@logical = false
			end
		end

		if field.pattern.size > 0
			if not value =~ /#{field.pattern.chardata[0].strip}/
				puts "\nERROR in field: #{field.title.chardata[0].strip}\n" +
							"value: \"#{value}\" does not match assigned regex pattern\n" +
							"pattern: #{field.pattern.chardata[0].strip}\n"
				@@logical = false
			end
		end
	end
end
