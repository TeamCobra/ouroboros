require 'rgen/instantiator/default_xml_instantiator'
require 'rgen/environment'
require 'rgen/template_language'
require './server_model'
require './logic_checker'

class XML
  attr_accessor :deviceConfig
end

if ARGV.empty? or ARGV.length > 1
	puts "Usage: ruby generator.rb <config.xml>"
	exit 1
end

if !File.exists?(ARGV[0])
	puts "Error: XML configuration file does not exist."
	exit 1
end	

env = RGen::Environment.new
inst = RGen::Instantiator::DefaultXMLInstantiator.new(env, ServerModel, true)
inst.instantiate_file(ARGV[0])

MODEL = XML.new
MODEL.deviceConfig = env.find(:class => ServerModel::DeviceConfig).first

TEMPLATES_DIR = "templates/"
OUTPUT_DIR = "./"

def generateCode
  tc = RGen::TemplateLanguage::DirectoryTemplateContainer.new([ServerModel], OUTPUT_DIR)
  tc.load(TEMPLATES_DIR)
  tc.expand('root::Root', :for => MODEL, :indent => 0)
end

lc = LogicChecker.new
lc.checkLogic(MODEL.deviceConfig)

generateCode

