#include <server/device_tree.tpp>
#include <data/base.hpp>
#include <data/base_string.h>
#include <data/base_integer.h>
#include <string>
#include <limits>

namespace ouroboros
{
   namespace detail
   {
      template<>
      group<var_field> build_tree()
      {
         group<var_field> result("server", "Root node.");
         result.add(new base_integer("A number", "A number for use in the program.", 20, {std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}));
         result.add(new base_string("A string", "", "", "", 10, {0, 10}));

         group<var_field> *group1 = new group<var_field>("Group 1", "This is Group 1.");
         group1->add(new base_string("A string inside group 1", "", "", "", 10, {0, 10}));

         group<var_field> *group2 = new group<var_field>("Group 2", "This is Group 2.");
         group2->add(new base_string("A string inside group 2", "", "", "", 10, {0, 10}));

         group1->add(group2);
         result.add(group1);

         return result;
      }
   }
}
