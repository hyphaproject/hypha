// Copyright (c) 2015-2017 Hypha

function doWork(){
    log("doWork()");
}

function setup(){
    text = '"setup"';
    log(text+"\n\n");
}

function communicate(message){
    var obj = JSON.parse(message);
    log("communicate()");
    log(obj.tell);
    return message;
}

function loadConfig(json){
    var obj = JSON.parse(json);
    log("loadConfig()");
}

function getConfig(){
    var obj = { "log":true };
    return JSON.stringify(obj);
}

function receiveMessage(message){
    log(message);
}
