module ServerModel
  extend RGen::MetamodelBuilder::ModuleExtension
  
  class Field < RGen::MetamodelBuilder::MMBase; end
  
  class Group < RGen::MetamodelBuilder::MMBase
    contains_many 'group', Group, 'parent'
    contains_many 'field', Field, 'parent'
  end
  
  class DeviceConfig < RGen::MetamodelBuilder::MMBase
    contains_many 'group', Group, 'parent'
    contains_many 'field', Field, 'parent'
  end
end