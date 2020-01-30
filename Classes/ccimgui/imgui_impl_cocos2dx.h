#pragma once

#include "imgui/imgui.h"

IMGUI_IMPL_API bool     ImGui_ImplCocos2dx_Init(bool install_callbacks);
IMGUI_IMPL_API void     ImGui_ImplCocos2dx_Shutdown();
IMGUI_IMPL_API void     ImGui_ImplCocos2dx_NewFrame();
IMGUI_IMPL_API void     ImGui_ImplCocos2dx_RenderDrawData(ImDrawData* draw_data);
IMGUI_IMPL_API void     ImGui_ImplOpenGL2_RenderDrawData(ImDrawData* draw_data);

// Called by Init/NewFrame/Shutdown
IMGUI_IMPL_API bool     ImGui_ImplCocos2dx_CreateDeviceObjects();
IMGUI_IMPL_API void     ImGui_ImplCocos2dx_DestroyDeviceObjects();
IMGUI_IMPL_API bool     ImGui_ImplCocos2dx_CreateFontsTexture();
IMGUI_IMPL_API void     ImGui_ImplCocos2dx_DestroyFontsTexture();



IMGUI_IMPL_API bool     ImGui_ImplOpenGL2_Init();
IMGUI_IMPL_API void     ImGui_ImplOpenGL2_Shutdown();
IMGUI_IMPL_API void     ImGui_ImplOpenGL2_NewFrame();
IMGUI_IMPL_API void     ImGui_ImplOpenGL2_RenderDrawData(ImDrawData* draw_data);

// Called by Init/NewFrame/Shutdown
IMGUI_IMPL_API bool     ImGui_ImplOpenGL2_CreateFontsTexture();
IMGUI_IMPL_API void     ImGui_ImplOpenGL2_DestroyFontsTexture();
IMGUI_IMPL_API bool     ImGui_ImplOpenGL2_CreateDeviceObjects();
IMGUI_IMPL_API void     ImGui_ImplOpenGL2_DestroyDeviceObjects();
