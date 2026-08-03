for /R %%a IN (*.dae) do IF EXIST "%%~pna.cached.dts" del "%%~pna.cached.dts"
for /R %%a IN (*.fbx) do IF EXIST "%%~pna.cached.dts" del "%%~pna.cached.dts"
for /R %%a IN (*.gltf) do IF EXIST "%%~pna.cached.dts" del "%%~pna.cached.dts"
for /R %%a IN (*.glb) do IF EXIST "%%~pna.cached.dts" del "%%~pna.cached.dts"