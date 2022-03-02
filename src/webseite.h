#ifndef WEBSITE_H
  #define WEBSITE_H
  #include <Arduino.h>
//Configseite
  const char CONF_page[] PROGMEM = R"=====( 
  <!DOCTYPE html>
  <html>

  <head>
      <title>ESP_Tuerklingel_Conf</title>
  </head>

  <body>
      <form action="/action_page">
          <table border=0>
              <thead>
                  <th colspan="2" align="center">
                      <h2>Einstellungen</h2>
                  </th>
              </thead>
              <tbody>
                  <tr>
                      <td colspan="2" align="center">Aktiv:<br>
                          <input type="checkbox" name="input_active" s_active
                              title="Klingel weiterleiten true oder false">
                      </td>
                  </tr>
                  <tr>
                      <td>Intervall:<br>
                          <input type="number" name="input_interval" value=s_interval
                              title="Pausenzeit in ms zwischen Klingeln"> ms
                      </td>
                      <td>
                          Klingelzeit:<br>
                          <input type="number" name="input_ringtime" value=s_ringtime
                              title="Wie lange der Rundruf klingelt in ms"> ms
                      </td>
                  </tr>
                  <tr>
                      <td><br><br>FritzBox Benutzer:<br>
                          <input type="text" name="input_user" value=s_user title="Benutzername">
                      </td>
                      <td><br><br>FB Benutzer Passwort:<br>
                          <input type="text" name="input_password" value=s_password title="Benutzerpasswort">
                      </td>
                  </tr>
                  <tr>
                      <td>FritzBox IP:<br>
                          <input type="text" name="input_fbip" value=s_fbip title="IP">
                      </td>
                      <td>FritzBox Port:<br>
                          <input type="number" name="input_port" value=s_port title="Port">
                      </td>
                  </tr>
                  <tr>
                      <td colspan="2" align="center"><br><input type="submit" value="Submit"></td>
                  </tr>
              </tbody>
          </table>
      </form>
  </body>

  </html>
    )=====";
#endif