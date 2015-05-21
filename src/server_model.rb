module ServerModel
  extend RGen::MetamodelBuilder::ModuleExtension
  
	class Title < RGen::MetamodelBuilder::MMBase; end
	class Description < RGen::MetamodelBuilder::MMBase; end
	class Value < RGen::MetamodelBuilder::MMBase; end
	class Min < RGen::MetamodelBuilder::MMBase; end
	class Max < RGen::MetamodelBuilder::MMBase; end
	class MinLength < RGen::MetamodelBuilder::MMBase; end
	class MaxLength < RGen::MetamodelBuilder::MMBase; end
	class Pattern < RGen::MetamodelBuilder::MMBase; end

  class Field < RGen::MetamodelBuilder::MMBase 
		contains_many 'title', Title, 'parent'
		contains_many 'description', Description, 'parent'
		contains_many 'value', Value, 'parent'
		contains_many 'min', Min, 'parent'
		contains_many 'max', Max, 'parent'
		contains_many 'minLength', MinLength, 'parent'
		contains_many 'maxLength', MaxLength, 'parent'
		contains_many 'pattern', Pattern, 'parent'
	end
  
  class Group < RGen::MetamodelBuilder::MMBase
    contains_many 'title', Title, 'parent'
    contains_many 'description', Description, 'parent'
    contains_many 'group', Group, 'parent'
    contains_many 'field', Field, 'parent'
  end
  
  class DeviceConfig < RGen::MetamodelBuilder::MMBase
    contains_many 'group', Group, 'parent'
    contains_many 'field', Field, 'parent'
  end
end
