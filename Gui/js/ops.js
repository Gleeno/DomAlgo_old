var settings;
var ws;
$(document).ready(function(){
});
    
angular.module("mainApp",[])
    .factory("initServices", function($http,$q) {
        
        return {
            init: function () {
                var res = {};
                var defered = $q.defer();
                $http.get("configs/default.json").then(function(result) {
                    res.sets = result.data;
                    var def2 = $q.defer();
                    var w = new WebSocket(res.sets.WS_ADDRESS + res.sets.WS_PORT,res.sets.WS_PROTOCOL);
                    res.w = w;
                    res.w.onopen=function(evt) {
                        def2.resolve(res);  
                        l("Connection opened.");
                    };                    
                    return def2.promise;
                }).then(function(result) {
                    defered.resolve(res);       
                });
                return defered.promise;
            }
        };
        
   })
   .controller('ctrl', function ($rootScope,$scope,$http,$q,initServices) {
        initServices.init().then(function(result) {
            $scope.settings = result.sets;
            $scope.ws = result.w;
            var msg = {
                        action: $scope.settings.A_PAIRING,
                        id : "term01",
                        type : 5, // TERMINAL
                        data: {
                            sensor: "all"
                        }
                       };
                       l("Action request: "+ msg.action);
            $scope.ws.send(JSON.stringify(msg));
           $scope.ws.onclose = function(evt) {
               $scope.$digest();
               l("Ws closed. ReadyState: "+$scope.ws.readyState);
                };
            $scope.ws.onerror = function(evt) {
               $scope.$digest();
                    l("Ws error. ReadyState: "+$scope.ws.readyState);
                };
            $scope.ws.onmessage = function(msg) {
                l("Message received: "+ msg.data);
                $scope.lastMsg = msg.data;
                $scope.$digest();
            }
       });
   });
        
    //UTIL
function l(message) {
    console.log("log[" + message + "]");          
}
//log user in div with id= log
function lu(message) {
    $("#log").append(message + "<br>");          
}
function lall(message) {
    l(message);
    lu(message);          
}