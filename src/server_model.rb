module ServerModel
  extend RGen::MetamodelBuilder::ModuleExtension
  class Field < RGen::MetamodelBuilder::MMBase
    include RGen::Ext::NavigationExtensions
  end
  class Group < RGen::MetamodelBuilder::MMBase
    include RGen::Ext::NavigationExtensions
    contains_many_uni 'group', Group
    contains_many_uni 'field', Field
  end
  class DeviceConfig < RGen::MetamodelBuilder::MMBase
    include RGen::Ext::NavigationExtensions
    contains_many_uni 'group', Group
    contains_many_uni 'field', Field
  end
end