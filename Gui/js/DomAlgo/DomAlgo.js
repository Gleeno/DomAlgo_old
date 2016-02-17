angular
        .module('DomAlgo',[
            'ngRoute',
            'loadSettingService',
            'getWsService',
        ])
        .config(configure)
        .run(runBlock);
        
configure.$inject = ["$routeProvider"];
runBlock.$inject = ["$http","$rootScope","loadSettingService", "getWsService"];

function configure(routeProvider) {
    routeProvider
            .when("/realTime", {
                templateUrl : "pages/realTime.html",
                controller : "realTime"
            })
            .when("/stats",{
                templateUrl : "pages/stats.html",
                controller : "stats"
            })
            .otherwise({ redirectTo : "" });
}
function runBlock(http, rootScope, loadSettingService, getWsService) {
    rootScope.loadingState=1;
    rootScope.settings = [];
    rootScope.ws = [];
    activate();
    
    function activate() {
        return getSetting().then(function() { 
                    console.log("Settings loaded.");
                    console.log("Ws opening..." + rootScope.settings.WS_ADDRESS);
                    return getWs()
                            .then(function() {
                                console.log("WebSokcket loaded: "+ rootScope.ws.readyState);
                                rootScope.loadingState=0;
                            });                   
                });
    function getSetting() {
        return loadSettingService.getSetting()
                .then(function(result) {
                    rootScope.settings = result.data;
                    return result;
                })
                .catch(function(error) {
                    console.log("?Error: "+ error.data);
                });
    }
    function getWs() {
        return getWsService.getWs(rootScope.settings.WS_ADDRESS,
                                  rootScope.settings.WS_PORT,
                                  rootScope.settings.WS_PROTOCOL)
                .then(function(result) {
                    rootScope.ws = result;
                })
                .catch(function(error) {
                    console.log("?Error: " + error.data);
                });
    }
    
    }
    function parseInstruction(instruction) {
        
    }
}