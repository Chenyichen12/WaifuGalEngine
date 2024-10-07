Android apk generate
```shell
androiddeployqt.exe
--input ${JSON_IN}
--output ${BUILD_DIR}
--android-platform ${ANDROID_PLATEFORM}
--jdk ${JDK}
--gradle


androiddeployqt.exe 
--verbose 
--output D:/code/WaifuGalEngine/build/${presetName}/engine/android-build 
--no-build 
--input D:/code/WaifuGalEngine/build/${presetName}/engine/android-WaifuGalEngine-deployment-settings.json 
--gradle --reinstall --device emulator-5554

adb.exe install  D:/code/WaifuGalEngine/build/${presetName}/engine/android-build/build/outputs/apk/debug/android-build-debug.apk
```

sample
```shell
D:\Qt\6.7.2\mingw_64\bin\androiddeployqt.exe --input D:/code/WaifuGalEngine/build/android_x86_64_user/engine/android-WaifuGalEngine-deployment-settings.json --output D:/code/WaifuGalEngine/build/android_x86_64_user/engine/android-build --android-platform android-34 --jdk C:/Users/chen_yichen/.jdks/corretto-17.0.9 --gradle

D:\Qt\6.7.2\mingw_64\bin\androiddeployqt.exe --verbose --output D:/code/WaifuGalEngine/build/android_x86_64_user/engine/android-build --no-build --input D:/code/WaifuGalEngine/build/android_x86_64_user/engine/android-WaifuGalEngine-deployment-settings.json --gradle --reinstall --device emulator-5554

D:\Android\Sdk\platform-tools\adb.exe install  D:/code/WaifuGalEngine/build/android_x86_64_user/engine/android-build//build/outputs/apk/debug/android-build-debug.apk

```
remove .git after configure the project


