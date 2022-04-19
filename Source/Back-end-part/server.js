// import { createServer } from 'https';
// import { readFileSync } from 'fs';
// import { WebSocketServer } from 'ws';
const https = require('https');
const fs = require('fs');
const wss = require('ws');
const mongodb = require('mongodb').MongoClient;
const net = require('net');
//create servers
const embedded = net.createServer();//TCP server
const server = https.createServer({
    cert: fs.readFileSync('./pem/cert.pem'),
    key: fs.readFileSync('./pem/key.pem')    
});//https server
const wssServer = new wss.WebSocketServer({ server });//WebSocket server
// listen to ports
embedded.listen(9002);
server.listen(9001);

//Function to encode string from embedded device
const encodeString = function(str){
    //three types of data: camera link, temperature and humidity
    //camera link string: '0tcp://0.0.0.0:port'
    //temp and humi string: '11999-01-01-00:00:00-25.00-40.00'
    var timestr = str.substr(1,10) + "T" + str.substr(12,8) + "Z";
    var timeobj = new Date(timestr);
    console.log(timeobj)
    var obj = {
        time: timeobj,
        value: [str.substr(21,5), str.substr(27)]//[temp, humi]
    };
    console.log(obj);
    return obj;
};
//Function to insert one data into database
const insertData = function(obj){
    mongodb.connect("mongodb://localhost:27017/", function(err, db) {
        if (err) throw err;
        var dbo = db.db("tempHumi");// connect to database tempHumi
        var tempobj = {time: obj.time, value: obj.value[0]};
        var humiobj = {time: obj.time, value: obj.value[1]};
        dbo.collection("temp").insertOne(tempobj, function(err, res) {
            if (err) throw err;
            console.log("insert succeed: " + "{ " + obj.time + ", " + obj.value[0] + " }");
        });

        dbo.collection("humi").insertOne(humiobj, function(err, res) {
            if (err) throw err;
            console.log("insert succeed: " + "{ " + obj.time + ", " + obj.value[1] + " }");
        });
    });
};
//Function to search hsitorical data
const searchData = function(str){
    mongodb.connect("mongodb://localhost:27017/", function(err, db) {
        var now = new Date();
        var onDay = 24 * 3600 * 1000;
        var threshold = new Date(+now - onDay).toISOString();
        threshold = new Date(threshold);
        
        if (err) throw err;
        
        var dbo = db.db("tempHumi");// connect to database tempHumi
        if (str == 'temp'){
            dbo.collection("temp").find({'time':{$gt:new Date(threshold)}}).toArray(function(err, result){
                if (err) throw err;
                
                wssSocket.send(JSON.stringify({type: "historicalTemp", value: result}));
            });
        }
        else if (str == 'humi'){
            dbo.collection("humi").find({'time':{$gt:new Date(threshold)}}).toArray(function(err, result){
                if (err) throw err;
                
                wssSocket.send(JSON.stringify({type: "historicalHumi", value: result}));
            });
        }
    });
    return true;
};
var wssSocket, embeddedSocket;

//embedded device connection
embedded.on('connection', function(socket){
    console.log("%s connected", socket.address().address);
    socket.on('close', function(){
        console.log("%s closed.\n", socket.address().address);
    });
    socket.on('data', function(data){
        data = data.toString();
        console.log("receive %s from %s", data, socket.address().address);
        var obj = {};
        if (data.substr(0,1) == '0'){//camera link
            obj.type = 'camera';
            obj.value = data.substr(1);
            if ((typeof wssSocket) == 'object') wssSocket.send(JSON.stringify(obj));
        }
        else{//temp or humi
            obj = encodeString(data);
            obj.type = 'real-time';
            insertData(obj);
            if ((typeof wssSocket) == 'object') wssSocket.send(JSON.stringify(obj));
        }
    });
});

wssServer.on('connection', function(ws) {
    wssSocket = ws;
    ws.on('message', function message(data) {
        data = data.toString();
        console.log('received: %s\n', data);
        if (data == 'CameraLink'){
            if ((typeof embeddedSocket) == 'object'){
                embeddedSocket.send('CameraLink');
            }
        }
        else if (data == 'historicalTemp'){
            searchData('temp');
        }
        else if (data == 'historicalHumi'){
            searchData('humi');
        }
    });
});