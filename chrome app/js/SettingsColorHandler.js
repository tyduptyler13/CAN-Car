

var home = document.getElementsByClassName("HomeTab");
var setting = document.getElementsByClassName("SettingsTab");
var music = document.getElementsByClassName("MusicTab");
var hvac = document.getElementsByClassName("HVACTab");
var navigate = document.getElementsByClassName("NavigationTab");
var data = document.getElementsByClassName("DataTab");
var HomeColorPressed = false;
var SettingColorPressed = false;
var MusicColorPressed = false;
var HVACColorPressed = false;
var NavigationColorPressed = false;
var DataColorPressed = false;


$("#HomeColor").click(function () {
    HomeColorPressed = true;
    SettingColorPressed = false;
    MusicColorPressed = false;
    HVACColorPressed = false;
    NavigationColorPressed = false;
    DataColorPressed = false;


    if (HomeColorPressed == true){
      $("#Green1").click(function () {
          document.getElementById("HomeBody").style.backgroundColor = "#99FF99";
          home[0].style.backgroundColor = "#99FF99";
      });
      $("#Green2").click(function () {
          document.getElementById("HomeBody").style.backgroundColor = "#66FF66";
          home[0].style.backgroundColor = "#66FF66";
      });
      $("#Green3").click(function () {
          document.getElementById("HomeBody").style.backgroundColor = "#33CC33";
          home[0].style.backgroundColor = "#33CC33";
      });
      $("#Green4").click(function () {
          document.getElementById("HomeBody").style.backgroundColor = "#009933";
          home[0].style.backgroundColor = "#009933";
      });
      $("#Green5").click(function () {
          document.getElementById("HomeBody").style.backgroundColor = "#336600";
          home[0].style.backgroundColor = "#336600";
      });
     }
	HomeColorPressed = false;
});

$("#SettingColor").click(function () {
    HomeColorPressed = false;
    SettingColorPressed = true;
    MusicColorPressed = false;
    HVACColorPressed = false;
    NavigationColorPressed = false;
    DataColorPressed = false;

    if (SettingColorPressed == true){
    $("#Blue1").click(function () {
        document.getElementById("SettingsBody").style.backgroundColor = "#66FFFF";
        setting[0].style.backgroundColor = "#66FFFF";
    });
    $("#Blue2").click(function () {
        document.getElementById("SettingsBody").style.backgroundColor = "#33CCFF";
        setting[0].style.backgroundColor = "#33CCFF";
    });
    $("#Blue3").click(function () {
        document.getElementById("SettingsBody").style.backgroundColor = "#0099FF";
        setting[0].style.backgroundColor = "#0099FF";
    });
    $("#Blue4").click(function () {
        document.getElementById("SettingsBody").style.backgroundColor = "#0033CC";
        setting[0].style.backgroundColor = "#0033CC";
    });
    $("#Blue5").click(function () {
        document.getElementById("SettingsBody").style.backgroundColor = "#000099";
        setting[0].style.backgroundColor = "#000099";
    });
   }
});

$("#MusicColor").click(function () {
    $("#Purple1").click(function () {
        document.getElementById("MusicBody").style.backgroundColor = "#CC99FF";
        music[0].style.backgroundColor = "#CC99FF";
    });
    $("#Purple2").click(function () {
        document.getElementById("MusicBody").style.backgroundColor = "#9999FF";
        music[0].style.backgroundColor = "#9999FF";
    });
    $("#Purple3").click(function () {
        document.getElementById("MusicBody").style.backgroundColor = "#9966FF";
        music[0].style.backgroundColor = "#9966FF";
    });
    $("#Purple4").click(function () {
        document.getElementById("MusicBody").style.backgroundColor = "#9933FF";
        music[0].style.backgroundColor = "#9933FF";
   });
    $("#Purple5").click(function () {
        document.getElementById("MusicBody").style.backgroundColor = "#6600CC";
        music[0].style.backgroundColor = "#6600CC";
    });
});