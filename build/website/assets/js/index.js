$(document).ready(function () {
  $.ajax({
    type: "GET",
    url: "/groups",
    dataType: "json"
  }).done(function(data) {
    $.each(data, function(groupName, data) {
      console.log(groupName);
      var liString = "<li role='presentation'>" + groupName + "</li>"; 
      console.log(liString);
      var $li = $(liString);
      $(".navbar").append($li);
    });    
  });
});
