function doGet(e) {
  return ContentService.createTextOutput(getStringFromSheet());
}

function getStringFromSheet() {
  var spreadsheetId = 'YOUR-ID-SPREADSHEET';
  var sheetName = 'uang-amal';

  var sheet = SpreadsheetApp.openById(spreadsheetId).getSheetByName(sheetName);
  var cellValue = sheet.getRange('J4').getValue();
  return cellValue;
}
