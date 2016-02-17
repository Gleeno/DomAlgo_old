angular
        .module('loadSettingService', [])
        .factory("loadSettingService",loadSetting);
loadSetting.$inject=["$http"];

function loadSetting(http) {
    return { getSetting : getSetting };
    
    function getSetting() {
        return http.get("configs/default.json")
                .then(getSettingComplete)
                .catch(getSettingFailed);
        
        function getSettingComplete(result) {
            return result;
        }
        
        function getSettingFailed(error) {
            console.log("Error loading settings: " + error.data);
        }
    };
}