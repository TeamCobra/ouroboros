require 'rgen/instantiator/default_xml_instantiator'
require 'rgen/environment'
require 'rgen/util/model_dumper'
require 'rgen/template_language'

module MyMM 
  class XML
    attr_accessor :personArray
  end
end
  
module MetaModel
    class PArray < RGen::MetamodelBuilder::MMBase
      has_attr 'name'
      has_attr 'size', Integer
      has_attr 'type'
    end
    class PrimitiveInitValue < RGen::MetamodelBuilder::MMBase
      has_attr 'value', String
    end
    PArray.has_many 'initvalue', PrimitiveInitValue
end

env = RGen::Environment.new
inst = RGen::Instantiator::DefaultXMLInstantiator.new(env, MetaModel, true)
inst.instantiate_file("manual_testmodel.xml")

house = env.find(:class => MetaModel::MNS_House).first
rooms = env.find(:class => MetaModel::MNS_Room)
persons = env.find(:class => MetaModel::Person)

puts persons

TEST_MODEL = MyMM::XML.new()
TEST_MODEL.personArray = MetaModel::PArray.new(:name => "people", :type => "string", :size => 4)

def test_with_model
  tc = RGen::TemplateLanguage::DirectoryTemplateContainer.new([MyMM, MetaModel], OUTPUT_DIR)
  tc.load(TEMPLATES_DIR)
  tc.expand('root::Root', :for => TEST_MODEL, :indent => 1)
end

TEMPLATES_DIR = "templates/"
OUTPUT_DIR = "output/"

puts TEST_MODEL.personArray.initvalue.value
test_with_model
