
function doWork(){
    text = '"doWork"';
}

function setup(){
    text = '"setup"';
    log(text+"\n\n");
}

function communicate(message){

    return message;
}

function loadConfig(json){

    text = json;
    print(text+"\n\n");
}

function getConfig(){
    return "{}";
}

function receiveMessage(message){
    log(message);
}
