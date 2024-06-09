function getCurrentDateTime() {
    var currentDate = new Date();
    var day = currentDate.getDate();
    var month = currentDate.getMonth() + 1;
    var year = currentDate.getFullYear();
    var hours = currentDate.getHours();
    var minutes = currentDate.getMinutes();
    var seconds = currentDate.getSeconds();

    var formattedDateTime = day + '/' + month + '/' + year + ' ' + hours + ':' + minutes + ':' + seconds;
    return formattedDateTime;
  }
  window.onload = function() {
    setTimeout(function() {
      var lastLoadedTimeElement = document.getElementById('last-update');
      lastLoadedTimeElement.innerHTML = getCurrentDateTime();
    }, 2500);
  };
  