const cluster = require("cluster");
const translate = require('node-google-translate-skidz');
const W3CWebSocket = require('websocket').w3cwebsocket;

if (cluster.isMaster) {
    console.log(`Master ${process.pid} is running`);

    for (let i = 0; i < 1; i++) {
        cluster.fork();
    }

    cluster.on('exit', (deadWorker, code, signal) => {
        var worker = cluster.fork();
    });

} else {
    var client = new W3CWebSocket('ws://localhost:9092/');

    client.onerror = function() {
        console.log('Connection Error');
    };

    client.onopen = function() {
        console.log('WebSocket Client Connected');
    };

    client.onclose = function() {
        console.log('Client Closed');
        process.exit(1);
    };

    client.onmessage = function(e) {
        console.log("msg received" + e.data);

        if (typeof e.data === 'string') {

            var splitted    = e.data.split("|");
            var id          = splitted[0];
            var type        = splitted[1];
            var msg         = splitted[2];
            var input       = splitted[3];
            var output      = splitted[4];

            if(type == "RAW") {

                translate({
                    text: msg,
                    source: input,
                    target: output
                }, function(result) {
                    client.send(id+"|TRANS|"+result["sentences"][0]["trans"]);
                    console.log(result["sentences"][0]["trans"]);
                });
            }
        }
    }
};
