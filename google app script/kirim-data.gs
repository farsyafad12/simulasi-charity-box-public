function doGet(e) {
  var sheet = SpreadsheetApp.openById("YOUR-ID-SPREADSHEET").getSheetByName("uang-amal");
  var data = sheet.getDataRange().getValues();
  
  // Validasi parameter
  if (!e.parameter.value || !e.parameter.status) {
    return ContentService.createTextOutput("Missing parameters");
  }

  var rowData = [];
  var now = new Date();
  var formattedDate = Utilities.formatDate(now, Session.getScriptTimeZone(), "yyyy-MM-dd HH:mm:ss");
  rowData.push(formattedDate);
  rowData.push(parseFloat(e.parameter.value));
  rowData.push(e.parameter.status === "true" ? true : false);

  // Temukan baris pertama yang kolom A, B, dan C-nya kosong
  for (var i = 0; i < data.length; i++) {
    if (!data[i][0] && !data[i][1] && !data[i][2]) {
      sheet.getRange(i + 1, 1, 1, rowData.length).setValues([rowData]);
      return ContentService.createTextOutput("Success");
    }
  }

  // Jika tidak ada baris yang kosong, tambahkan baris baru
  sheet.appendRow(rowData);
  
  return ContentService.createTextOutput("Success");
}
