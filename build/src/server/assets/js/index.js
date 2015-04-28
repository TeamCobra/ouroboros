$(document).ready(function () {
  nav = new Nav();

  // load in the tabs for navigation
  makeNavBar(nav);

  $(".navbar").click("a", getGroup);  
  $(".navbar").click("a", nav.setActive);  
  $("body").submit(".field-form", updateField); 

});

function updateField(e) {
  e.preventDefault();

  // get the form, its url, and value(theres only one)
  var $form = $(e.target);
  var url = $form.attr("action");
  var updateValue = $form.find("input").val();

  // submit an update request, refresh the page on done
  $.ajax({
    url: url,
    type: "PUT",
    contentType: "application/json",
    data: JSON.stringify({ value: updateValue})
  }).done(function(data) {
    var groupId = $('.navbar li.active').data('group-id')
    // refresh data by getting page info again and reloading the page
    $.getJSON("/groups/" + groupId, function(data) { 
      var rootTitle = $('.navbar li.active').data("group-id");
      loadPage(data); 
    });
  });
}

function getGroup(e) {
  // get the navigation link clicked
  var li = $(e.target).parent()
  var classes = li.attr("class");
  // if its not active, change the content
  if (classes == undefined || classes == "" || !classes.includes("active")) {
    // pull off the group id for a GET request
    var url = "/groups/" + li.data("group-id")
    // get the json for the page and load it
    $.getJSON(url, function(data) {
      var rootTitle = $('.navbar li.active').data("group-id");
      loadPage(data);
    })
  }
}


function makeNavBar(nav) { 
  var index = 0;
  // get the index json for groups, this is universal
  // across all xml inputs so we can get all info
  $.getJSON("/groups", function(json) {
    // iterate through the first level depth 
    $.each(json.contents, function(id, data) {
      // if there is no value, its a group
      if (data.value == undefined) {
        // add it to the navigation section
        nav.add(data.title, index, id);
      } else {
        // it its not a group add it as input
        // to the main content section
        var input = new Input(id, data);
        $(".page").append(input.$el);
      }
      
      // if this iteration is for the first menu item,
      // make it active and load its contents
      if (index == 0 && data.type == "group") {
        nav.initActive(0);
        loadPage(data, id);
      }
      
      index++;
    });       
  });
}

function loadPage(data, rootTitle) {
  // clear whatever is in the main content area now
  $(".page").html("");

  // put in the title and description
  var $title = $("<h2>" + data.title + "</h2>");
  var $desc = $("<p>" + data.description + "</p>");

  $(".page").append($title);
  $(".page").append($desc);

  // iterate through the elements in the page
  $.each(data.contents, function(id, sectionData) {
    // if its a group, add the section header
    if (sectionData.type == "group") {
      var rootTitle = $(".active").data("group-id")
      var subGroup = new SubGroup(sectionData.title, id, true);

      addSubGroup(id, sectionData, subGroup);
      subGroup.buildUrls(rootTitle);
    } else {
      // for a field, build the url and put it in the input
      var url = "/groups/" + $(".active").data("group-id") + "/fields/"
      var input = new Input(id, sectionData, url);
      $(".page").append(input.$el);
    }
  });
}


/* 
 * Subgroup and Input related code
 */

// takes in the name and the contained data for a given subgroup
// and adds inputs as well as recursively adding any extra subgroups
function addSubGroup(name, data, parent) {
  $.each(data.contents, function(id, contents) {
    // if we have a nested group, recurse
    if (contents.type == "group") {
      var subGroup = new SubGroup(contents.title, id);
      parent.subgroups.push(subGroup);
      addSubGroup(id, contents, subGroup);
      parent.$el.find('.body-content').eq(0).append(subGroup.$el);
    } else {
      // if not a group, add input to the SubGroup object
      parent.addInput(id, contents);
    } 
  })
  $(".page").append(parent.$el);
}

// SubGroup holds some easy to access attributes as well as its DOM
// element. This allows for us to go through after fully loading a 
// page and adding the full urls easily
function SubGroup(name, id, top) {
  this.subgroups = [];
  this.inputs = [];

  this.name = name;
  this.id = id;

  // top is passed in if it is the first-level group on the content section. The first-level groups have a bootstrap panel with
  // colored headings while the subsequent levels have just a lined-border nested inside it's parents
  if (top) {
    this.$el = $( '<div class="panel panel-default">' +
                    '<div class="panel-heading">' + 
                      name + 
                    '</div>' +
                    '<div class="panel-body body-content">' + 
                    '</div>' +
                  '</div>');
  } else {
    this.$el = $( '<li class="list-group-item deep-group">' + 
                    '<h3>' + 
                      name + 
                    '</h3>' +
                    '<div class="body-content">' +
                    '</div>' +
                  '</li>');
  }
}


// Handles making a new input and putting it in the subgroup's internal
// inputs variable as well as in the DOM
SubGroup.prototype.addInput = function(id, contents) {
  var input = new Input(id, contents);
  this.inputs.push(input);
  this.$el.find('.body-content').eq(0).append(input.$el);
}

SubGroup.prototype.buildUrls = function(url) {
  base = url + "." + this.id;

  // creates a url for the fields inside this subgroup and places it in the 
  // input's individual forms' action attribute
  $.each(this.inputs, function(i, input) {
    var url = "/groups/" + base + "/fields/" + input.name;
    input.$el.attr("action", url);
  });

  // recursively call buildUrls with any subgroups, passing the new modified
  // base url with the current subgroup's id appended to it
  $.each(this.subgroups, function(i, subgroup) {
    subgroup.buildUrls(base);
  });
}


// Input is used to hold state of an input field and easily allow us to
// hold it in a SubGroup for final page loading
function Input(name, data, baseUrl) {
  // make a copy of the hidden template in the DOM
  this.$el = $($('#input-template').html()).clone()

  // keep a copy of name for when building urls
  this.name = name;

  // set the range if there is one
  if (data.range) {
    var range = data.range[0] + " to " + data.range[1];
    this.$el.find('input').attr("placeholder", range);
  }

  // set the form type
  switch (data.type) {
  case "base_integer":
    this.$el.find('input').attr("type","number")
    break;
  default:
    // its a string or will be soon
    this.$el.find('input').attr("type","text")
    break;
  }

  // add tooltip functionality if there is a description
  if (data.description) {
    this.$el.attr("data-toggle","tooltip");
    this.$el.attr("data-placement","left");
    this.$el.attr("title",data.description);
    this.$el.tooltip();
  }

  // make the base URL and add it in
  var url = baseUrl + name;
  this.$el.attr("action", url);

  // fill in information for the label
  var $span = this.$el.find('#name-value-label')
  var nameValueLabel = data.title + " : " + data.value
  $span.text(nameValueLabel);
}




/*
 * Nav Object Section and subsections
 */

function Nav() {
  this.groupLinks = []
}

// build and add nav links (GroupLinks) to the internal
// list that Nav keeps
Nav.prototype.add = function(groupName, id, groupId) {
  link = new GroupLink();
  link.$el.find("a").text(groupName);
  link.$el.attr("data-id", id);
  link.$el.attr("data-group-id", groupId);

  this.groupLinks.push(link);
  $('.navbar').append(link.$el);
}

// initActive is used primarily for setting the first link
// on initial page load
Nav.prototype.initActive = function(i) {
  this.groupLinks[i].$el.addClass("active");
}

// after initActive, setActive is used for all other clicks 
// on a navigation link
Nav.prototype.setActive = function(e) {
  $(".navbar li").removeClass("active");
  $(e.target.parentElement).addClass("active");
}

function GroupLink() {
  this.$el = $('<li role="presentation"><a href="#"></a></li>');
}