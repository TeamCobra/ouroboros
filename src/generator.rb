require 'rgen/instantiator/default_xml_instantiator'
require 'rgen/environment'
require 'rgen/template_language'
require './server_model'

class XML
  attr_accessor :deviceConfig
end

env = RGen::Environment.new
inst = RGen::Instantiator::DefaultXMLInstantiator.new(env, ServerModel, true)
inst.instantiate_file("serverconfig.xml")

MODEL = XML.new
MODEL.deviceConfig = env.find(:class => ServerModel::DeviceConfig).first

def generateCode
  tc = RGen::TemplateLanguage::DirectoryTemplateContainer.new([ServerModel], OUTPUT_DIR)
  tc.load(TEMPLATES_DIR)
  tc.expand('root::Root', :for => MODEL, :indent => 0)
end

TEMPLATES_DIR = "templates/"
OUTPUT_DIR = "../target/"

generateCode