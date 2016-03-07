angular
    .module("DomAlgoInstruction", [])
    .factory("DomAlgoInstruction", instruction);
instruction.$inject = ["$rootScope", "$timeout"];

function instruction(rootScope, timeout) {
    return {
        sendMessage: sendMessage,
        parseInstruction: parseInstruction
    };

    function sendMessage(action) {
        console.log("Invio istruzione...." + action);
        rootScope.ws.send(JSON.stringify(makeInstruction(action)));
    }

    function makeInstruction(action) {
        var instruction;

        instruction = {
            action: action,
            id: "all",
            type: 1,
            data: {}
        };
        console.log(instruction);
        return instruction;
    }
    function parseInstruction(message) {
        if (typeof message === "string") {
            //instruction = filterUnicode(message);
            console.log("string");
            message = JSON.parse(message.data);
            if (isSynapsisInstruction(message)) {
                //ACTIONS
                if (message.action === rootScope.settings.A_NOTIFY) {
                    console.log("Notify from server: " + message.data);
                }
                if (message.action === rootScope.settings.A_GET_DATA_SENSOR) {
                    for(var s in message.data.sensor) {
                        console.log(s);
                        rootScope.sensors.push(s);
                    }
                }
            }

            else if (message instanceof Blob) {
                //ws.binaryType = "arraybuffer";
                console.log("Blob data");
            }
            else if (message instanceof ArrayBuffer) {
                console.log("ArrayBuffer. " + message.byteLength);
            }
        }
        function isSynapsisInstruction(message) {
            if (message === undefined
                || message.action === undefined
                || message.id === undefined
                || message.data === undefined) {
                console.log("Wrong instruction format");
                return false;
            }
            console.log("Right instruction format");
            return true;
        }
    }
}
/*
 function sendMessage(raw) {
 // Wait until the state of the socket is not ready and send the message when it is...
 waitForSocketConnection(function () {
 console.log("message sent. Action: " + A_GET_DATA_SENSOR);
 if (raw === rootScope.settings.A_GET_DATA_SENSOR)
 rootScope.ws.send(JSON.stringify(A_GET_DATA_SENSOR));
 
 else if (raw === rootScope.settings.A_PAIRING)
 rootScope.ws.send(JSON.stringify(A_PAIRING));
 });
 }
 
 function waitForSocketConnection(callback) {
 timeout(
 function () {
 if (rootScope.ws || rootScope.ws.readyState) {
 console.log("Connection is made");
 if (callback !== null) {
 callback();
 }
 return;
 
 } else {
 console.log("wait for connection...");
 waitForSocketConnection(callback);
 }
 }, 500);
 }
 }
 */
