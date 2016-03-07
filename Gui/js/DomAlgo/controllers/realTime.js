angular
    .module("DomAlgoRealTime", ["DomAlgoInstruction"])
    .controller("DomAlgoRealTime", realTime);
realTime.$inject = ["$scope", "$rootScope", "$q", "DomAlgoInstruction"];

function realTime(scope, rootScope, q, DomAlgoInstruction) {
    rootScope.$on("isAllReady",init);
    function init(pars) {
            DomAlgoInstruction.sendMessage(rootScope.settings.A_PAIRING);
            DomAlgoInstruction.sendMessage(rootScope.settings.A_GET_DATA_SENSOR);
        //interval(update,1000);
    }
}