var DomAlgo = angular
    .module('DomAlgo', [
        'ngRoute',
        'loadSettingService',
        'getWsService',
        'DomAlgoRealTime',
        'DomAlgoInstruction'
    ])
    .config(configure)
    .run(runBlock);

configure.$inject = ["$routeProvider", "$locationProvider"];
runBlock.$inject = ["$http", "$rootScope", "loadSettingService", "getWsService","DomAlgoInstruction"];

function configure(routeProvider, locationProvider) {
    routeProvider
        .when("/", {
            templateUrl: "pages/realTime.html",
            controller: "DomAlgoRealTime"
        })
        .when("/realTime", {
            templateUrl: "pages/realTime.html",
            controller: "DomAlgoRealTime"
        })
        .when("/stats", {
            templateUrl: "pages/stats.html",
            controller: "stats"
        })
        .when("/behaviour", {
            templateUrl: "pages/behaviour.html",
            controller: "behaviour"
        })
        .otherwise({redirectTo: ""});
    
}
function runBlock(http, rootScope, loadSettingService, getWsService, DomAlgoInstruction) {
    rootScope.loadingState = 1;
    rootScope.isAllReady=0;
    rootScope.settings = [];
    rootScope.log = "";
    rootScope.sensors = [];
  
    rootScope.ws;
    activate();

    function activate() {
        return getSetting().then(function () {
            console.log("Settings loaded.");
            console.log("Ws opening..." + rootScope.settings.WS_ADDRESS);
            return getWs()
                .then(function () {
                    console.log("WebSokcket loaded: " + rootScope.ws.readyState);
                    rootScope.loadingState = 0;
                    rootScope.$emit("isAllReady", "on");
                });
        });
        function getSetting() {
            return loadSettingService.getSetting()
                .then(function (result) {
                    rootScope.settings = result.data;
                    return result;
                })
                .catch(function (error) {
                    console.log("?Error: " + error.data);
                });
        }
        function getWs() {
            return getWsService.getWs(rootScope.settings.WS_ADDRESS,
                rootScope.settings.WS_PORT,
                rootScope.settings.WS_PROTOCOL)
                .then(function (result) {
                    rootScope.ws = result;
                    rootScope.ws.onmessage = onMessage;
                })
                .catch(function (error) {
                    console.log("?Error: " + error.data);
                });
        }

    }
    function onMessage(message) {
        console.log("Message received: " + message.data);
        DomAlgoInstruction.parseInstruction(message.data);
    }
}