#include <stdio.h>
#include <string>
#include <thread>
#include <chrono>
#include "Engine.h"
#include "Connector.h"
#include "AppTicker.h"
#include "Timer.h"
#include "Converter.h"


#ifdef   DOS_WINDOWS
#ifdef   DDEBUG
#pragma comment(linker, "/subsystem:console /entry:mainCRTStartup")
//#pragma comment(linker, "/subsystem:console /entry:mainWCRTStartup")
#else
#pragma comment(linker, "/subsystem:console /entry:mainCRTStartup")
//#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
//#pragma comment(linker, "/subsystem:windows /entry:mainWCRTStartup")
#endif  //release version

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "ws2_32.lib")
#endif



namespace app {

void AppTestNetAddress();
void AppTestTree2heap();
void AppTestStrConv();
void AppTestDict();
void AppTestBase64();
void AppTestMD5();
void AppTestStr();
void AppTestVector();
void AppTestRBTreeMap();
s32 AppTestThreadPool(s32 argc, s8** argv);
s32 AppTestStrConvGBKU8(s32 argc, s8** argv);

s32 AppTestNetServer(s32 argc, s8** argv);
s32 AppTestNetClient(s32 argc, s8** argv);
s32 AppTestRedis(s32 argc, s8** argv);
s32 AppTestDefault(s32 argc, s8** argv);
s32 AppTestHttpsClient(s32 argc, s8** argv);

} //namespace app



using namespace app;



int main(int argc, char** argv) {
    printf("main>>start AntTest,argc=%d,argv[0]=%s\n", argc, argv[0]);
    if (argc < 2) {
        return 0;
    }
    printf("main>>cmd=%s\n", argv[1]);
    const s32 cmd = App10StrToS32(argv[1]);

    Engine& eng = Engine::getInstance();
    if (!eng.init(argv[0])) {
        printf("main>> engine init fail\n");
        return 0;
    }
    s32 ret = 0;
    switch (cmd) {
    case 0:
        //exe 0 0.0.0.0:9981 tls/tcp
        ret = 4 == argc ? AppTestNetServer(argc, argv) : argc;
        break;
    case 1:
        //exe 1 0.0.0.0:9981 tls/tcp 10 5000
        ret = 6 == argc ? AppTestNetClient(argc, argv) : argc;
        break;
    case 2:
        //exe 2
        ret = 2 == argc ? AppTestDefault(argc, argv) : argc;
        break;
    case 3:
        //exe 3
        ret = 2 == argc ? AppTestThreadPool(argc, argv) : argc;
        break;
    case 4:
        //exe 4
        ret = 2 == argc ? AppTestRedis(argc, argv) : argc;
        break;
    case 5:
        //exe 5
        ret = 2 == argc ? AppTestHttpsClient(argc, argv) : argc;
        break;
    default:
        if (true) {
            AppTestStrConvGBKU8(argc, argv);
        } else {
            AppTestThreadPool(argc, argv);
            AppTestStr();
            AppTestNetAddress();
            AppTestVector();
            AppTestRBTreeMap();
            AppTestStr();
            AppTestMD5();
            AppTestBase64();
            AppTestDict();
            AppTestTree2heap();
            AppTestStrConv();
        }
        break;
    }

    Logger::log(ELL_INFO, "main>>exit...");
    Logger::flush();
    eng.uninit();
    printf("main>>stop\n");
    return 0;
}