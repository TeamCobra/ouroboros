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
			if min < absoluteMin
				puts "\nERROR in field: #{field.title.chardata[0].strip}\nmin: #{min} is outside of range " + 
							"for data type #{field.type}\n#{field.type} range: #{absoluteMin} - #{absoluteMax}\n\n"
				exit 1
			end
			if value < min
				puts "\nERROR in field: #{field.title.chardata[0].strip}\nvalue: #{value} is lower than the assigned min" +
							"\nmin: #{min}\n\n"				
				exit 1
			end
		else
			if value < absoluteMin
				puts "\nERROR in field: #{field.title.chardata[0].strip}\nvalue: #{value} is outside of range " + 
							"for data type #{field.type}\n#{field.type} range: #{absoluteMin} - #{absoluteMax}\n\n"
				exit 1
			end
		end
		
		if defined? field.max and not field.max.empty?
			!decimal ? max = field.max.chardata[0].strip.to_i : max = field.max.chardata[0].strip.to_f 
			if max > absoluteMax
				puts "\nERROR in field: #{field.title.chardata[0].strip}\nmax: #{max} is outside of range " + 
							"for data type #{field.type}\n#{field.type} range: #{absoluteMin} - #{absoluteMax}\n\n"
				exit 1
			end
			if value > max
				puts "\nERROR in field: #{field.title.chardata[0].strip}\nvalue: #{value} is greater than the assigned max" +
							"\nmax: #{max}\n\n"
							exit 1
			end
		else
			if value > absoluteMax
				puts "\nERROR in field: #{field.title.chardata[0].strip}\nvalue: #{value} is outside of range " + 
							"for data type #{field.type}\n#{field.type} range: #{absoluteMin} - #{absoluteMax}\n\n"
				exit 1
			end
		end
	end

	def checkStringField(field)
		value = field.value.chardata[0].strip
		if defined? field.minLength and not field.minLength.empty?
			minLength = field.minLength.chardata[0].strip.to_i
			if value.length < minLength
				puts "\nERROR in field: #{field.title.chardata[0].strip}\nvalue: \"#{value}\" length (#{value.length}) "+
							"is lower than the assigned minlength \nminLength: #{minLength}\n\n"
				exit 1
			end
		end

		if defined? field.maxLength and not field.maxLength.empty?
			maxLength = field.maxLength.chardata[0].strip.to_i
			if value.length > maxLength
				puts "\nERROR in field: #{field.title.chardata[0].strip}\nvalue: \"#{value}\" length (#{value.length}) "+
							"is greater than the assigned maxlength \nmaxLength: #{maxLength}\n\n"
				exit 1
			end
		end

		if defined? field.pattern and not field.pattern.empty?
			if not value =~ /#{field.pattern.chardata[0].strip}/
				puts "\nERROR in field: #{field.title.chardata[0].strip}\nvalue: \"#{value}\" does not match assigned regex pattern"+
							"\npattern: #{field.pattern.chardata[0].strip}\n\n"
				exit 1
			end
		end
	end
end
