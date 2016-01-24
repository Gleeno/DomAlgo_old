$(document).ready(function(){
});
angular.module("mainApp",['ngWebSocket'])
        .controller('ctrl', function ($scope, $q, $rootScope, $http) {
            $http.get("configs/default.json")
            .success(function(data){
                lall("Settings load");
                $scope.settings=data;
                var wsI = new WebSocket("ws://"+
                                        $scope.settings.WSI_ADDRESS + ":" +
                                        $scope.settings.WSI_PORT, 
                                        $scope.settings.WSI_PROTOCOL);
                wsI.onopen = function() {
                    lall("wsI opened. Result state: " + wsI.readyState);
                    wsI.send("asdasd");
                }
            })
            .error(function(){
                lall("Error settings not load");
            });
        })
        
    
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