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
  class Field < RGen::MetamodelBuilder::MMBase
    has_attr 'id'
    has_attr 'name'
    has_attr 'structName'
    has_attr 'title'
    has_attr 'type'
  end
  class Server < RGen::MetamodelBuilder::MMBase
    has_attr 'port'
    has_attr 'response'
  end
  Server.has_many 'fields', Field
end

XML_MODEL = Model::XML.new()

env = RGen::Environment.new
inst = RGen::Instantiator::DefaultXMLInstantiator.new(env, MetaModel, true)
inst.instantiate_file("hello.xml")

server = env.find(:class => MetaModel::Server)[0]
fields = env.find(:class => MetaModel::Field)

XML_MODEL.server = MetaModel::Server.new(:port => server.port, :response => server.response,
  :fields => fields.collect{ |field| MetaModel::Field.new(:id => field.id, :name => field.name, :structName => field.structName, :title => field.title, :type => field.type) })

puts XML_MODEL.server.fields
    
def generateCode
  tc = RGen::TemplateLanguage::DirectoryTemplateContainer.new([Model, MetaModel], OUTPUT_DIR)
  tc.load(TEMPLATES_DIR)
  tc.expand('root::Root', :for => XML_MODEL, :indent => 0)
end

TEMPLATES_DIR = "templates/"
OUTPUT_DIR = "output/"

generateCode