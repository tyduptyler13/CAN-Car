
/*********Class for manipulating and displaying energy graph***************/
var EnergyChart = function (id, optionalChartData, optionalChartOptions) {

    this.ctx = document.getElementById(id).getContext("2d");
    var chart = new Chart(this.ctx);
    //Use passed in data if it was passed in
    if (optionalChartData !== undefined) {
        this.chartData = optionalChartData;
    }
    else {
        this.chartData =
        {
            labels: ["10", "9", "8", "7","6","5","4","3","2","1","0"],
            datasets: []
        };
    }

    //Use passed in options if they were passed in
    if (optionalChartOptions !== undefined) {
        this.chartOptions = optionalChartOptions;
    }
    else {
        this.chartOptions = {
            animation: false,
            scaleFontSize: 20
        };
    }

    this.lineGraph = chart.Line(this.chartData, this.chartOptions);

    //Redraw chart with data and options passed in
    var reDrawChart = function (inChartData, options) {
        this.lineGraph = chart.Line(inChartData, options);
    }

    /*
    //Add a single x,y pair to the data
    this.addData = function (dataX, dataValue) {
        this.chartData.labels.push(dataX);
        this.chartData.datasets[0].data.push(dataValue);
        reDrawChart(this.chartData, this.chartOptions);
    }
    */

    //Change data used in chart and refresh chart
    this.changeChartData = function (inData) {
        this.chartData = inData;
        reDrawChart(this.chartData, this.chartOptions);
    }

    //Change options used in chart and refresh chart
    this.changeChartOptions = function (inOptions) {
        this.chartOptions = inOptions;
        reDrawChart(this.chartData, this.chartOptions);
    }
    /*
    //Remove a data set if it is in the chart
    this.removeDataIfExists = function(fieldName) {
        for (var x = 0; x < this.chartData.datasets.length; x++) {
            if (this.chartData.datasets[x].name === fieldName) {
                this.chartData.datasets.splice(x, 1);
                this.changeChartData(this.chartData);
                return true;
            }
        }
    }
    */
    this.removeAllDatasets = function () {
        this.chartData.datasets.splice(0, this.chartData.datasets.length);
    }

    //Turns on and off the particular line in the chart
    //according to what is passed in
    this.toggleLine = function (settings) {
        this.removeAllDatasets()
        this.chartData.datasets.push(settings);
        this.changeChartData(this.chartData);
    }
}


