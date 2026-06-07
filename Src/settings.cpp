#include "settings.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

// Global theme settings instance
ThemeSettings gThemeSettings;

// Default theme settings initialization
void SetDefaultTheme() {
    // Window colors
    gThemeSettings.WindowBg = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    gThemeSettings.ChildBg = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
    gThemeSettings.PopupBg = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    
    // Text colors
    gThemeSettings.Text = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    gThemeSettings.TextDisabled = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    
    // Button colors
    gThemeSettings.Button = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    gThemeSettings.ButtonHovered = ImVec4(0.36f, 0.69f, 1.00f, 1.00f);
    gThemeSettings.ButtonActive = ImVec4(0.16f, 0.49f, 0.88f, 1.00f);
    
    // Frame colors
    gThemeSettings.FrameBg = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    gThemeSettings.FrameBgHovered = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    gThemeSettings.FrameBgActive = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    
    // Input colors
    gThemeSettings.InputText = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    gThemeSettings.InputBorder = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    
    // Font settings
    gThemeSettings.FontSize = 24.0f;
    gThemeSettings.FontPath = "data/font/Main.ttf";
    
    // Rounding settings
    gThemeSettings.WindowRounding = 8.0f;
    gThemeSettings.FrameRounding = 4.0f;
}

// Calculate relative luminance of a color (0 = dark, 1 = light)
float CalculateLuminance(ImVec4 color) {
    return 0.2126f * color.x + 0.7152f * color.y + 0.0722f * color.z;
}

// Apply theme to ImGui
void ApplyTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    
    // Window colors
    style.Colors[ImGuiCol_WindowBg] = gThemeSettings.WindowBg;
    style.Colors[ImGuiCol_ChildBg] = gThemeSettings.ChildBg;
    style.Colors[ImGuiCol_PopupBg] = gThemeSettings.PopupBg;
    
    // Calculate background luminance and auto-adjust text color
    float bgLuminance = CalculateLuminance(gThemeSettings.WindowBg);
    ImVec4 autoTextColor = (bgLuminance > 0.5f) ? ImVec4(0.0f, 0.0f, 0.0f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    ImVec4 autoTextDisabled = (bgLuminance > 0.5f) ? ImVec4(0.5f, 0.5f, 0.5f, 1.0f) : ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    
    // Text colors (auto-adjust based on background)
    style.Colors[ImGuiCol_Text] = autoTextColor;
    style.Colors[ImGuiCol_TextDisabled] = autoTextDisabled;
    style.Colors[ImGuiCol_TextSelectedBg] = (bgLuminance > 0.5f) ? ImVec4(0.7f, 0.7f, 0.7f, 1.0f) : ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    
    // Button colors
    style.Colors[ImGuiCol_Button] = gThemeSettings.Button;
    style.Colors[ImGuiCol_ButtonHovered] = gThemeSettings.ButtonHovered;
    style.Colors[ImGuiCol_ButtonActive] = gThemeSettings.ButtonActive;
    
    // Calculate auto frame background color based on window background
    // Light background: frame is slightly darker
    // Dark background: frame is slightly lighter
    float frameOffset = (bgLuminance > 0.5f) ? -0.15f : 0.15f;
    ImVec4 autoFrameBg = ImVec4(
        gThemeSettings.WindowBg.x + frameOffset,
        gThemeSettings.WindowBg.y + frameOffset,
        gThemeSettings.WindowBg.z + frameOffset,
        1.0f
    );
    
    // Clamp values to [0, 1]
    autoFrameBg.x = (autoFrameBg.x < 0.0f) ? 0.0f : (autoFrameBg.x > 1.0f) ? 1.0f : autoFrameBg.x;
    autoFrameBg.y = (autoFrameBg.y < 0.0f) ? 0.0f : (autoFrameBg.y > 1.0f) ? 1.0f : autoFrameBg.y;
    autoFrameBg.z = (autoFrameBg.z < 0.0f) ? 0.0f : (autoFrameBg.z > 1.0f) ? 1.0f : autoFrameBg.z;
    
    // Frame colors (auto-adjust based on background)
    style.Colors[ImGuiCol_FrameBg] = autoFrameBg;
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(
        autoFrameBg.x + (bgLuminance > 0.5f ? -0.05f : 0.05f),
        autoFrameBg.y + (bgLuminance > 0.5f ? -0.05f : 0.05f),
        autoFrameBg.z + (bgLuminance > 0.5f ? -0.05f : 0.05f),
        1.0f
    );
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(
        autoFrameBg.x + (bgLuminance > 0.5f ? -0.1f : 0.1f),
        autoFrameBg.y + (bgLuminance > 0.5f ? -0.1f : 0.1f),
        autoFrameBg.z + (bgLuminance > 0.5f ? -0.1f : 0.1f),
        1.0f
    );
    
    // Input border color
    style.Colors[ImGuiCol_Border] = gThemeSettings.InputBorder;
    
    // Rounding settings
    style.WindowRounding = gThemeSettings.WindowRounding;
    style.FrameRounding = gThemeSettings.FrameRounding;
}

// External declaration for font reload function
extern void ReloadFont(float fontSize);

// Render settings window
void RenderSettingsWindow(bool* showSettings) {
    // Settings window
    if (*showSettings) {
        ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_Once);
        if (ImGui::Begin("主题设置", showSettings, ImGuiWindowFlags_NoResize)) {
            // Font settings (disabled for now due to reload issues)
            ImGui::SeparatorText("字体设置");
            
            ImGui::TextDisabled("字体缩放功能暂不可用，请等待官方修复");
            // ImGui::PushItemWidth(200);
            // ImGui::SliderFloat("字体大小##disabled", &gThemeSettings.FontSize, 12.0f, 48.0f, "%.1f px", ImGuiSliderFlags_None);
            // ImGui::PopItemWidth();
            
            // Commented out due to font reload issues
            // if (ImGui::Button("应用字体")) {
            //     ReloadFont(gThemeSettings.FontSize);
            // }
            
            // Rounding settings
            ImGui::SeparatorText("圆角设置");
            
            ImGui::PushItemWidth(150);
            ImGui::InputFloat("窗口圆角", &gThemeSettings.WindowRounding, 1.0f, 2.0f, "%.1f");
            ImGui::InputFloat("输入框圆角", &gThemeSettings.FrameRounding, 1.0f, 2.0f, "%.1f");
            ImGui::PopItemWidth();
            
            // Clamp rounding values
            if (gThemeSettings.WindowRounding < 0.0f) gThemeSettings.WindowRounding = 0.0f;
            if (gThemeSettings.WindowRounding > 20.0f) gThemeSettings.WindowRounding = 20.0f;
            if (gThemeSettings.FrameRounding < 0.0f) gThemeSettings.FrameRounding = 0.0f;
            if (gThemeSettings.FrameRounding > 10.0f) gThemeSettings.FrameRounding = 10.0f;
            
            // Color settings
            ImGui::SeparatorText("颜色设置");
            
            ImGui::ColorEdit3("窗口背景", (float*)&gThemeSettings.WindowBg, ImGuiColorEditFlags_NoAlpha);
            ImGui::ColorEdit3("按钮颜色", (float*)&gThemeSettings.Button, ImGuiColorEditFlags_NoAlpha);
            ImGui::ColorEdit3("按钮悬停", (float*)&gThemeSettings.ButtonHovered, ImGuiColorEditFlags_NoAlpha);
            
            // Apply button
            if (ImGui::Button("应用主题")) {
                ApplyTheme();
            }
            
            // Reset button
            ImGui::SameLine();
            if (ImGui::Button("恢复默认")) {
                SetDefaultTheme();
                ApplyTheme();
            }
        }
        ImGui::End();
    }
}
