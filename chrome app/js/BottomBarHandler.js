var date;
var am_pm;
var hour;
var minute;
var WifiIsOn = false;
var BlueToothIsOn = false;
var VolumeBar = 0;

$(function(){
// set the battery image and percentage


setInterval(function () {
if (batteryPercentage >= 95) {
        document.getElementById("batteryImage").src = "images/Battery-Levels-100-PercentT.png";
}
else if (batteryPercentage >= 85) {
        document.getElementById("batteryImage").src = "images/Battery Levels 90 Percent.png";
}
else if (batteryPercentage >= 75) {
        document.getElementById("batteryImage").src = "images/Battery Levels 80 Percent copy.png";
}
else if (batteryPercentage >= 65) {
        document.getElementById("batteryImage").src = "images/Battery Levels 70 Percent copy.png";
}
else if (batteryPercentage >= 55) {
        document.getElementById("batteryImage").src = "images/Battery Levels 60 Percent copy.png";
}
else if (batteryPercentage >= 45) {
        document.getElementById("batteryImage").src = "images/Battery Levels 50 Percent copy.png";
}
else if (batteryPercentage >= 35) {
        document.getElementById("batteryImage").src = "images/Battery Levels 40 Percent.png";
}
else if (batteryPercentage >= 25) {
        document.getElementById("batteryImage").src = "images/Battery Levels 30 Percent copy.png";
}
else if (batteryPercentage >= 15) {
        document.getElementById("batteryImage").src = "images/Battery Levels 20 Percent copy.png";
}
else if (batteryPercentage >= 5) {
        document.getElementById("batteryImage").src = "images/Battery Levels 10 Percent copy.png";
}
else document.getElementById("batteryImage").src = "images/Battery-Levels-0-Percent.png";

}, 500);


setInterval(function () {
    document.getElementById("Battery_Text").innerHTML = batteryPercentage + "%";
}, 1000);

//display the time
setInterval(function () {
    date = new Date();
    am_pm;
    hour = date.getHours();
    minute = date.getMinutes();
    if (hour > 12) {
        am_pm = "PM";
        hour = hour - 12;
    }
    else {
        am_pm = "AM";
    }
    if (hour == 0) {
        hour = 12;
    }
    if (minute < 10) {
        document.getElementById("Clock").innerHTML = hour + ":0" + minute + " " + am_pm;
    }
    else document.getElementById("Clock").innerHTML = hour + ":" + minute + " " + am_pm;

}, 1000);

//wifi on/off

$("#WifiOn").click(function () {
    if (WifiIsOn == false) {
        WifiIsOn = true;
        document.getElementById("WifiImage").src = "images/Wi-Fi On 3 bars.png";
    }
    else {
        WifiIsOn = false;
        document.getElementById("WifiImage").src = "images/Wi-Fi_Off.png";
    }
});

//BlueTooth on/off
$("#BlueTooth").click(function () {
    if (BlueToothIsOn == false) {
        BlueToothIsOn = true;
        document.getElementById("BlueToothImage").src = "images/Bluetooth On.png";
    }
    else {
        BlueToothIsOn = false;
        document.getElementById("BlueToothImage").src = "images/Bluetooth Off.png";
    }
});

$("#VolumeUp").click(function () {
    if (VolumeBar < 4) {
        VolumeBar++;
    }
    switch (VolumeBar) {
        case 1: {
            document.getElementById("VolumeLevel").src = "images/Volume 0 Bars.png";
        }
            break;
        case 2: {
            document.getElementById("VolumeLevel").src = "images/Volume 1 Bars.png";
        }
            break;
        case 3: {
            document.getElementById("VolumeLevel").src = "images/Volume 2 Bars.png";
        }
            break;
        default: {
            document.getElementById("VolumeLevel").src = "images/Volume 3 Bars.png";
        }
            break;
    }
});

$("#VolumeDown").click(function () {
    if (VolumeBar > 0) {
        VolumeBar--;
    }
    switch (VolumeBar) {

        case 1: {
            document.getElementById("VolumeLevel").src = "images/Volume 0 Bars.png";
        }
            break;
        case 2: {
            document.getElementById("VolumeLevel").src = "images/Volume 1 Bars.png";
        }
            break;
        case 3: {
            document.getElementById("VolumeLevel").src = "images/Volume 2 Bars.png";
        }
            break;
        default: {
            document.getElementById("VolumeLevel").src = "images/Volume Mute copy.png";
        }
            break;
    }
});
});