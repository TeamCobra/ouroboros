require 'nokogiri'

schema = Nokogiri::XML::Schema(File.read('exampleSchema.xsd'))
document = Nokogiri::XML(File.read('example.xml'))

puts schema.validate document