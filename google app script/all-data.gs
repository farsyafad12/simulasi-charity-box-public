function myFunction() {
  var spreadsheetId = 'YOUR-ID-SPREADSHEET';
  var sheetName = 'uang-amal';
  
  var spreadsheet = SpreadsheetApp.openById(spreadsheetId);
  var sheet = spreadsheet.getSheetByName(sheetName);
  
  var range = sheet.getRange("A2:C");  // Mulai dari baris kedua
  var values = range.getValues();
  
  var htmlOutput = "";

  for (var i = 0; i < values.length; i++) {
    var row = values[i];
    if (row[0] === "" && row[1] === "" && row[2] === "") {
      break;
    }
    
    // Format tanggal
    var formattedDate = Utilities.formatDate(new Date(row[0]), "GMT+7", "yyyy-MM-dd HH:mm:ss");
    
    htmlOutput += "<tr><td>" + formattedDate + "</td><td>" + row[1] + "</td><td>" + row[2] + "</td></tr>\n";
  }
  
  Logger.log(htmlOutput);
  
  return htmlOutput;
}

function doGet(e) {
  var htmlOutput = "<thead>" +
                   "<tr>" +
                   "<th>Waktu</th>" +
                   "<th>Jumlah</th>" +
                   "<th>Status</th>" +
                   "</tr>" +
                   "</thead>" +
                   "<tbody>" +
                   myFunction() +
                   "</tbody>";
  return ContentService.createTextOutput(htmlOutput).setMimeType(ContentService.MimeType.HTML);
}
