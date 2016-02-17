angular
        .module('getWsService',[])
        .factory("getWsService", getWebSocket);
getWebSocket.$inject = ["$rootScope", "$q","$http"];

function getWebSocket(rootScope,q,http) {
    return { getWs : getWs };
    
    function getWs(address, port,protocol) {
       return asyncWs(address)
               .then(getWsComplete)
               .catch(getWsFailed);   
       function asyncWs() {
        var deferred = q.defer();
        var ws = new WebSocket(address+port,protocol);
        ws.onopen = onOpen;
        ws.onerror = onError;
        ws.onclose = onClose;
        return deferred.promise;
        
        function onOpen() {
                //console.log("readyState: " + ws.readyState);
                deferred.resolve(ws);
        }
        function onError() {
            console.log("Error: ");
        }
        function onClose() {
            console.log("Ws closed");
        }
    }
    
    function getWsComplete(result) {
        return result;
    }
    function getWsFailed(error) {
        console.log("Error: " + error.data);
    }
    }
    
} 