const wss = new WebSocket('wss://pssite.website:9001');
//Function to change the Unit of temperature.
let changeUnit = function(){
    let img = document.getElementById('temp_img');
    let temp = document.getElementById('temp');
    let now = document.getElementById('tempUnit');
    //℃ to ℉
    if (now.value == 'C'){
        temp.value = (Number(temp.value.substr(0,temp.value.length -1)) * 1.8 + 32).toFixed(2).toString() + '℉';
        img.src = 'picture/temp_F.jpg';
        now.value = 'F';
    }
    //℉ to ℃
    else {
        temp.value = (Number(temp.value.substr(0,temp.value.length -1) - 32) / 1.8).toFixed(2).toString() + '℃';
        img.src = 'picture/temp_C.jpg';
        now.value = 'C';
    }
};
let showTemp = function(tempobj,tempstr){
    let unit = document.getElementById('tempUnit');
    if (unit.value == 'C')
        tempobj.value = tempstr + tempobj.value.substr(-1,1);
    else {
        tempobj.value = (Number(tempstr) * 1.8 + 32).toFixed(2) + tempobj.value.substr(-1,1);
    }
}
//Function to requst the camera link
let getCameraLink = function(){
    wss.send('CameraLink');
};
// Connection opened
wss.addEventListener('open', function (event) {
    wss.send('Real-time socket connected.');
});
//show chart
var realTimeTemp = echarts.init(document.getElementById("realTimeTempChart"));
var realTimeHumi = echarts.init(document.getElementById("realTimeHumiChart"));
var historicalTemp = echarts.init(document.getElementById("historicalTempChart"));
var historicalHumi = echarts.init(document.getElementById("historicalHumiChart"));
var app = {};
var realTimeTempOption;
var realTimeHumiOption;
var historicalTempOption;
var historicalHumiOption;
//function to process data
var now = new Date();
function randomData(timeAxis, tempData, humiData) {
    for (var i = 0; i < 60; i++){
        now = new Date(+now + 1000 * i);
        tempData.push({
            name: [now.getFullYear(), now.getMonth(), now.getDate()].join('-') + " " + now.getHours(),
            value: '-'
        });
        humiData.push({
            name: [now.getFullYear(), now.getMonth(), now.getDate()].join('-') + " " + now.getHours(),
            value: '-'
        });
        timeAxis.push([now.getMinutes(), now.getSeconds()].join(':'));
    }
}
let timeAxis = [];
let tempData = [];
let humiData = [];
let HtempData = [];
let HhumiData = [];
let initicialData = [];
//give real-time humi and temp initicial data
randomData(timeAxis, tempData, humiData);
//real-time temp chart option
realTimeTempOption = {
    title: {
        text: 'Real-time value of temperature'
    },
    tooltip: {
        trigger: 'axis',
        formatter: function (params) {
            params = params[0];
            return (
                params.name + ' => ' + params.value
            );
          },
        axisPointer: {
        animation: false
        }
    },
    xAxis: {
        type: 'category',
        name: tempData[0].name,
        nameLocation: 'center',
        data: timeAxis,
        nameGap: 30,
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
        name: 'tempData',
        type: 'line',
        showSymbol: 'circle',
        data: tempData
        }
    ]
};
realTimeHumiOption = {
    title: {
        text: 'Real-time value of humidity'
    },
    tooltip: {
        trigger: 'axis',
        formatter: function (params) {
            params = params[0];
            return (
                params.name + ' => ' + params.value
            );
          },
        axisPointer: {
        animation: false
        }
    },
    xAxis: {
        type: 'category',
        name: humiData[0].name,
        nameLocation: 'center',
        data: timeAxis,
        nameGap: 30,
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
        name: 'humiData',
        type: 'line',
        showSymbol: 'pin',
        data: humiData
        }
    ]
};
// historicalTempOption = {
//     title: {
//         text: 'Historical value of temperature'
//     },
//     tooltip: {
//         trigger: 'axis',
//         formatter: function (params) {
//         params = params[0];
//         var date = new Date(params.name);
//         return (
//             date.getDate() +
//             '/' +
//             (date.getMonth() + 1) +
//             '/' +
//             date.getFullYear() +
//             ' : ' +
//             params.value[1]
//         );
//         },
//         axisPointer: {
//         animation: false
//         }
//     },
//     xAxis: {
//         type: 'time',
//         splitLine: {
//         show: true
//         }
//     },
//     yAxis: {
//         type: 'value',
//         boundaryGap: [0, '100%'],
//         splitLine: {
//         show: true
//         }
//     },
//     series: [
//         {
//         name: 'HtempData',
//         type: 'line',
//         showSymbol: false,
//         data: HtempData
//         }
//     ]
// };
// historicalHumiOption = {
//     title: {
//         text: 'Historical value of humidity'
//     },
//     tooltip: {
//         trigger: 'axis',
//         formatter: function (params) {
//         params = params[0];
//         var date = new Date(params.name);
//         return (
//             date.getDate() +
//             '/' +
//             (date.getMonth() + 1) +
//             '/' +
//             date.getFullYear() +
//             ' : ' +
//             params.value[1]
//         );
//         },
//         axisPointer: {
//         animation: false
//         }
//     },
//     xAxis: {
//         type: 'time',
//         splitLine: {
//         show: true
//         }
//     },
//     yAxis: {
//         type: 'value',
//         boundaryGap: [0, '100%'],
//         splitLine: {
//         show: true
//         }
//     },
//     series: [
//         {
//         name: 'HhumiData',
//         type: 'line',
//         showSymbol: false,
//         data: HhumiData
//         }
//     ]
// };
//Timer, call the function every 1 second
setInterval(function () {
    realTimeTemp.setOption({
        series: [
        {
            data: tempData
        }
        ]
    });

    realTimeHumi.setOption({
        series: [
        {
            data: humiData
        }
        ]
    });
    
    // historicalTemp.setOption({
    //     series: [
    //     {
    //         data: HtempData
    //     }
    //     ]
    // });
    
    // historicalHumi.setOption({
    //     series: [
    //     {
    //         data: HhumiData
    //     }
    //     ]
    // });
}, 1000);

if (realTimeTempOption && typeof realTimeTempOption === 'object') {
    realTimeTemp.setOption(realTimeTempOption);
};
if (realTimeHumiOption && typeof realTimeHumiOption === 'object') {
    realTimeHumi.setOption(realTimeHumiOption);
};
// if (historicalTempOption && typeof historicalTempOption === 'object') {
//     historicalTemp.setOption(historicalTempOption);
// };
// if (historicalHumiOption && typeof historicalHumiOption === 'object') {
//     historicalHumi.setOption(historicalHumiOption);
// };

wss.addEventListener('message', function (event) {
    let data = event.data;
    //console.log('Message from server ', data);
    //Update the text that indicates real-time temperature and humidity.
    data = JSON.parse(data);
    if (data.type == 'real-time'){//temperature data
        let temp = document.getElementById('temp');
        var tempStr = Number(data.value[1]).toFixed(2);
        var timeStr = new String(data.time);
        timeStr = timeStr.split("");
        timeStr[10] = 'T';
        timeStr = timeStr.join('');
        var timeobj = new Date(timeStr);
        // temp.value = tempStr + temp.value.substr(-1,1);
        showTemp(temp, tempStr);
        tempData.shift();
        tempData.push({
            name: [timeobj.getFullYear(), timeobj.getMonth(), 
                timeobj.getDate()].join('-') + " " + timeobj.getHours(),
            value: tempStr
            });
        //humidity data
        let humi = document.getElementById('humi');
        var humiStr = Number(data.value[0]).toFixed(2);
        humi.value = humiStr + '%';
        humiData.shift();
        humiData.push({
            name: [timeobj.getFullYear(), timeobj.getMonth(), 
                timeobj.getDate()].join('-') + " " + timeobj.getHours(),
            value: humiStr
        });
    }
    else if (data.type == 'Historical'){// historical temperature data

    }
});
