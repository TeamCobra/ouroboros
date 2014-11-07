require 'nokogiri'

schema = Nokogiri::XML::Schema(File.read('schema.xsd'))
document = Nokogiri::XML(File.read('example.xml'))

puts schema.validate document