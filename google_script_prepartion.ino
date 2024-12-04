function doGet(e) {
  var sheet = SpreadsheetApp.openById('Solar Sense').getActiveSheet();
  var action = e.parameter.action;

  if (action === 'logData') {
    var temperature = e.parameter.temperature;
    var humidity = e.parameter.humidity;
    var airQuality = e.parameter.airQuality;
    var dustConcentration = e.parameter.dustConcentration;
    var windFrequency = e.parameter.windFrequency;
    var timestamp = new Date();
    sheet.appendRow([timestamp, temperature, humidity, airQuality, dustConcentration, windFrequency]);
    return ContentService.createTextOutput("Data logged");
  } else {
    return ContentService.createTextOutput("Invalid action");
  }
}
