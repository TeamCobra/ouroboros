require 'rgen/instantiator/default_xml_instantiator'
require 'rgen/environment'
require 'rgen/util/model_dumper'
require 'rgen/template_language'

module Model
  class XML
    attr_accessor :server
  end
end

module MetaModel
  class Server < RGen::MetamodelBuilder::MMBase; end
end

XML_MODEL = Model::XML.new()

env = RGen::Environment.new
inst = RGen::Instantiator::DefaultXMLInstantiator.new(env, MetaModel, true)
inst.instantiate_file("serverconfig.xml")

XML_MODEL.server = env.find(:class => MetaModel::Server)[0]
  
def generateCode
  tc = RGen::TemplateLanguage::DirectoryTemplateContainer.new([MetaModel], OUTPUT_DIR)
  tc.load(TEMPLATES_DIR)
  tc.expand('root::Root', :for => XML_MODEL, :indent => 0)
end

TEMPLATES_DIR = "templates/"
OUTPUT_DIR = "../target/"

generateCode