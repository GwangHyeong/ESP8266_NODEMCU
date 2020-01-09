
const char pageSecond[] PROGMEM =R"=====(

<!doctype html>
<html>
<head>
<title>Seconds Page</title>
</head>
<body>
<h1>This is Second page</h1>
<h2>Dept. of SmartMedia</h2>

<p><a href="/">Main Page</a></p>
<p><a href="/second_page">Second Page</a></p>
<p><a href="/thrid_page">Thrid page</a></p>

<form action ="/action_page" method='get'>
Device name:<br>
<input type="text" name="device" value="led">
<br>
Control data : <br>
<input type="text" name="On/Off number" size="40" value="On/OFF number">
<br><br>
<input type="submit" value="submit">
</form>
</body>
</html>
)=====";

