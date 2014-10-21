require 'rgen/instantiator/default_xml_instantiator'
require 'rgen/environment'
require 'rgen/util/model_dumper'
require 'rgen/template_language'

module MetaModel 
  class XML
    attr_accessor :server
  end
end
  
module FieldModel
  module MNS
    class Value < RGen::MetamodelBuilder::MMBase; end 
  end
  class Field < RGen::MetamodelBuilder::MMBase; end
  
  Field.one_to_one 'fieldValue', MNS::Value, 'test'

  class Server < RGen::MetamodelBuilder::MMBase
    has_attr 'response'
    has_attr 'port'
  end
end

class MyInstantiator < RGen::Instantiator::DefaultXMLInstantiator
  map_tag_ns "testmodel.org/myNamespace", FieldModel::MNS
  resolve_by_id :fieldValue, :id => :getId, :src => :value
end

env = RGen::Environment.new
inst = MyInstantiator.new(env, FieldModel, true)
inst.instantiate_file("hello.xml")

fields = env.find(:class => FieldModel::Field)
response = fields[0].fieldValue.chardata[0].strip
port = fields[1].fieldValue.chardata[0].strip

TEST_MODEL = MetaModel::XML.new()
TEST_MODEL.server = FieldModel::Server.new(:response => response, :port => port)

def generateCode
  tc = RGen::TemplateLanguage::DirectoryTemplateContainer.new([MetaModel, FieldModel], OUTPUT_DIR)
  tc.load(TEMPLATES_DIR)
  tc.expand('root::Root', :for => TEST_MODEL, :indent => 0)
end

TEMPLATES_DIR = "templates/"
OUTPUT_DIR = "output/"

generateCode