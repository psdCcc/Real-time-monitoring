const realTimeSocket = new WebSocket('wss://pssite.website:9001');
const chartSocket = new WebSocket('wss://pssite.website:9002');
//Function to change the Unit of temperature.
let changeUnit = function(){
    let img = document.getElementById('temp_img');
    let temp = document.getElementById('temp');
    let now = document.getElementById('tempUnit');
    //℃ to ℉
    if (now.value == 'C'){
        temp.value = (temp.value.substr(0,temp.value.length -1).valueOf() * 1.8 + 32).toFixed(2).toString() + '℉';
        img.src = 'picture/temp_F.jpg';
        now.value = 'F';
    }
    //℉ to ℃
    else {
        temp.value = ((temp.value.substr(0,temp.value.length -1).valueOf() - 32) / 1.8).toFixed(2).toString() + '℃';
        img.src = 'picture/temp_C.jpg';
        now.value = 'C';
    }
};
//Function to requst the camera link
let getCameraLink = function(){
    chartSocket.send('CameraLink');
};
// Connection opened
realTimeSocket.addEventListener('open', function (event) {
    realTimeSocket.send('Real-time socket connected.');
});
chartSocket.addEventListener('open', function(event) {
    chartSocket.send('Chart socket connected.');
});
// Listen for messages
realTimeSocket.addEventListener('message', function (event) {
    let data = event.data;
    console.log('Message from server ', data);
    let temp = document.getElementById('temp');
    let humi = document.getElementById('humi');
    //Update the text that indicates real-time temperature and humidity.
    humi.value = data.humi.valueOf().toFixed(2).toString() + '%';
    temp.value = data.temp.valueOf().toFixed(2).toString() + temp.value.substr(value.lenght - 1,1);

});
chartSocket.addEventListener('message', function(event) {
    let data = event.data;
    console.log('Message from server ', data);
    //receive the camera link
    if (data.type == 'camera'){
        let camera = document.getElementById('cameraLink');
        camera.value = data.value;
    }
    //receive the historical temperature data
    else if (data.type == 'temp'){

    }
    //receive the historical humidity data
    else {

    }
});

var domTemp = document.getElementById("tempChart");
var domHumi = document.getElementById("humiChart");
var tempChart = echarts.init(domTemp);
var humiChart = echarts.init(domHumi);
var app = {};

var tempOption;
var humiOption;



function randomData() {
now = new Date(+now + oneDay);
value = value + Math.random() * 21 - 10;
return {
    name: now.toString(),
    value: [
    [now.getFullYear(), now.getMonth() + 1, now.getDate()].join('/'),
    Math.round(value)
    ]
};
}
let data = [];
let now = new Date();
let oneDay = 24 * 3600 * 1000;
let value = Math.random() * 1000;
for (var i = 0; i < 1000; i++) {
data.push(randomData());
}
tempOption = {
    title: {
        text: 'Real-time value of temperature'
    },
    tooltip: {
        trigger: 'axis',
        formatter: function (params) {
        params = params[0];
        var date = new Date(params.name);
        return (
            date.getDate() +
            '/' +
            (date.getMonth() + 1) +
            '/' +
            date.getFullYear() +
            ' : ' +
            params.value[1]
        );
        },
        axisPointer: {
        animation: false
        }
    },
    xAxis: {
        type: 'time',
        splitLine: {
        show: true
        }
    },
    yAxis: {
        type: 'value',
        boundaryGap: [0, '100%'],
        splitLine: {
        show: true
        }
    },
    series: [
        {
        name: 'Fake Data',
        type: 'line',
        showSymbol: false,
        data: data
        }
    ]
};
humiOption = {
    title: {
        text: 'Real-time value of humidity'
    },
    tooltip: {
        trigger: 'axis',
        formatter: function (params) {
        params = params[0];
        var date = new Date(params.name);
        return (
            date.getDate() +
            '/' +
            (date.getMonth() + 1) +
            '/' +
            date.getFullYear() +
            ' : ' +
            params.value[1]
        );
        },
        axisPointer: {
        animation: false
        }
    },
    xAxis: {
        type: 'time',
        splitLine: {
        show: true
        }
    },
    yAxis: {
        type: 'value',
        boundaryGap: [0, '100%'],
        splitLine: {
        show: true
        }
    },
    series: [
        {
        name: 'Fake Data',
        type: 'line',
        showSymbol: false,
        data: data
        }
    ]
};
setInterval(function () {
for (var i = 0; i < 5; i++) {
    data.shift();
    data.push(randomData());
}
humiChart.setOption({
    series: [
    {
        data: data
    }
    ]
});

tempChart.setOption({
    series: [
    {
        data: data
    }
    ]
});
}, 1000);

if (tempOption && typeof tempOption === 'object') {
    tempChart.setOption(tempOption);
};
if (humiOption && typeof humiOption === 'object') {
    humiChart.setOption(humiOption);
};