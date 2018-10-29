var langs = JSON.parse(data);
var mom         = this;
var messages    = [];
var errors      = [];
var SpeechRecognition = window.webkitSpeechRecognition;
var recognition = new SpeechRecognition();

recognition.lang = "fr-FR";
recognition.continuous = true;

recognition.onstart = function() {
    console.log("Started recognition");
}

recognition.onerror = function(event) {
    errors.push("Started recognition");
}

recognition.onend = function() {
    recognition.start();
}

recognition.onresult = function(event) {

    if(event.results && event.results.length > 0 ) {
        
        var uniqueID = (new Date()).getTime();

        var input  = langs[select_language.selectedIndex][1];
        var	output = langs[translate_language.selectedIndex][1];

		var transcript = event.results[event.results.length-1][0].transcript;
		console.log(event.results[event.results.length-1][0].confidence);
        if (event.results[event.results.length-1][0].confidence > 0.8) {
			ws.send(uniqueID+"|RAW|"+transcript+"|"+input[0]+"|"+output[0]);
            console.log("from "+input+" to "+ output);
            updateField(transcript);
        
        }else{
        	recognition.lang = output[0];
            recognition.stop();
    
            temp = select_language.selectedIndex; 
            select_language.selectedIndex = translate_language.selectedIndex;
            translate_language.selectedIndex = temp;

            input   = langs[select_language.selectedIndex][1];
        	output  = langs[translate_language.selectedIndex][1];

        	console.log("from "+input+" to "+ output)
            if (input[0]=="fr-FR"){
                ws.send(uniqueID+"|RAW|"+"changement de langue"+"|"+input[0]+"|"+output[0]);
            }else{
                ws.send(uniqueID+"|RAW|"+"changement de langue"+"|"+output[0]+"|"+input[0]);
            }

            updateField("<p style='color:green;'> changement de langue");
        }

        
    }    
}

recognition.start();


function updateField(message) {
    
    messages.push("<p>"+message+"</p>");
    var txt = "";
    for( var i = messages.length - 1; i >=0; i--) {
        txt += messages[i];
        
    }
    $("#transcripts").html(txt);
    
}

// set interval for weird bug
// this will stop the recognition, onend event is shot, then recognition is back again
// ¯\_(ツ)_/¯
setInterval(resetVoiceRecog, 10000);
var t = this;
function resetVoiceRecog() {
    t.recognition.stop();
}


$('#select_language').on('change', function() {
    recognition.lang = langs[this.value][1];
    recognition.stop();
})

$('#scenario_id').on('change', function() {
    ws.send(this.value+"|SCENARIO_CHANGE|NULL|NULL|NULL");
})

function createWebSocket(server) {
    for (i = scenario_id.options.length; i > 0; i--) {
        scenario_id.options[i] = null;
    }
    scenario_id.options[0] = new Option("Auto", 0);
    scenario_id.selectedIndex = 0;
    if ("WebSocket" in window) {
        try {
            ws = new WebSocket("ws://" + server + ":9092/");
        } catch (err) {
            $(".lead").html("<p style='color:red;'>Error in WebSocket connection.</p>");
        }
        
        ws.onopen = function (error) {
            $(".lead").html("<p style='color:green;'>Up and running</p>");
            if(window.timerID){
                window.clearInterval(window.timerID);
                window.timerID=0;
            }
        };
        
        ws.onclose = function (error) {
            $(".lead").html("<p style='color:red;'>Websocket has been closed.</p>");
            $("#scenario_id").empty();
            scenario_id.options[0] = new Option("Auto", 0);
            if(!window.timerID){
                window.timerID = setInterval(
                    function () {
                        createWebSocket(
                            document.getElementById("ip_selection").value
                        );
                    }, 5000);
               }
        };
        
        ws.onerror = function (error) {
            $(".lead").html("<p style='color:red;'>Error in WebSocket connection.</p>");
        };
        
        
        ws.onmessage = function (evt) {
            var received_msg    = evt.data;
            var splitted        = received_msg.split("|");
            var id              = splitted[0];
            var type            = splitted[1];
            var msg             = splitted[2];
            
            if(type == "TRANS")
                updateField("<p style='color:red;'>"+msg+"</p>");
            if (type == "SCENARIO_DATA")
                scenario_id.options[parseInt(id) + 1] = new Option(msg, parseInt(id) + 1);
        };
    
    } else {
        alert("Y a même pas WebSocket sur ce navigateur. C'est fini IE6");
    }
}

$('#ip_selection').on('change', function() {
    createWebSocket(this.value);
});

$('#refresh_bt').on('click', function() {
    createWebSocket(
        document.getElementById("ip_selection").value
    );
});

createWebSocket("localhost");


for (var i = 0; i < langs.length; i++) {
    select_language.options[i] = new Option(langs[i][0], i);
}

for (var i = 0; i < langs.length; i++) {
    translate_language.options[i] = new Option(langs[i][0], i);
}
select_language.selectedIndex       = 14;
translate_language.selectedIndex    = 11;
