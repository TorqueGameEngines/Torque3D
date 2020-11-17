
function Core_SFX::onCreate(%this)
{
   exec("./scripts/audio.ts");
   exec("./scripts/audioData.ts");
   exec("./scripts/audioAmbience.ts");
   exec("./scripts/audioDescriptions.ts");
   exec("./scripts/audioEnvironments.ts");
   exec("./scripts/audioStates.ts");

}

function Core_SFX::onDestroy(%this)
{
}