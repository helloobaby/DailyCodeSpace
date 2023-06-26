// D:\workspace\PluginTemplate\src\plugin.cpp

#include "plugin.h"

// Examples: https://github.com/x64dbg/x64dbg/wiki/Plugins
// References:
// - https://help.x64dbg.com/en/latest/developers/plugins/index.html
// - https://x64dbg.com/blog/2016/10/04/architecture-of-x64dbg.html
// - https://x64dbg.com/blog/2016/10/20/threading-model.html
// - https://x64dbg.com/blog/2016/07/30/x64dbg-plugin-sdk.html



static ULONG_PTR bp_address;
static void bp_callback(CBTYPE cbType, void* callbackInfo) {
    PLUG_CB_BREAKPOINT* callbackInfo2 = (PLUG_CB_BREAKPOINT*)callbackInfo;
    if (callbackInfo2->breakpoint->addr == bp_address) {
        auto rax = Script::Register::GetRAX();
        dprintf(">> api address = %llx\n", rax);
        const char* func_name = (const char*)ImporterGetAPIName(rax);
        if (func_name && !stricmp(func_name, "GetProcAddress")) {
            auto rdx = Script::Register::GetRDX();
            
            // 多读一点问题不大
            char temp[256]{};
            MemoryReadSafe(DbgGetProcessHandle(), (PVOID)rdx, temp, sizeof(temp), NULL);
            dprintf(">> call : %s\n", temp);
            
        }
        else if (func_name) {
            dprintf(">> call : %s\n", func_name);
        }
        DbgCmdExec("r");
    }
}
static bool cbExampleCommand(int argc, char** argv)
{
    dprintf(">> start \n");

    auto base = GetDebuggedFileBaseAddress();
    dprintf(">> base : %llx\n", base);

    ULONG_PTR offset = 0x63cdc;

    bp_address = offset + base;
    dprintf(">> want to bp at %llx\n", bp_address);

    // 设置断点
    Script::Debug::SetBreakpoint(bp_address);
    // 添加断点回调
    _plugin_registercallback(pluginHandle, CB_BREAKPOINT, bp_callback);
    DbgCmdExec("cls");
    return true;
}

// Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
    dprintf("pluginInit(pluginHandle: %d)\n", pluginHandle);

    // Prefix of the functions to call here: _plugin_register
    _plugin_registercommand(pluginHandle, PLUGIN_NAME, cbExampleCommand, true);

    // Return false to cancel loading the plugin.
    return true;
}

// Deinitialize your plugin data here.
// NOTE: you are responsible for gracefully closing your GUI
// This function is not executed on the GUI thread, so you might need
// to use WaitForSingleObject or similar to wait for everything to close.
void pluginStop()
{
    // Prefix of the functions to call here: _plugin_unregister

    dprintf("pluginStop(pluginHandle: %d)\n", pluginHandle);
}

// Do GUI/Menu related things here.
// This code runs on the GUI thread: GetCurrentThreadId() == GuiGetMainThreadId()
// You can get the HWND using GuiGetWindowHandle()
void pluginSetup()
{
    // Prefix of the functions to call here: _plugin_menu

    dprintf("pluginSetup(pluginHandle: %d)\n", pluginHandle);
}
