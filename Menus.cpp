#include "Page.hpp"

#include <sstream>
#include <iomanip>
#include <string>
#include <signal.h>
#include <sys/types.h>

std::string floatToFormattedString(float value) {
    std::ostringstream oss;
    oss << std::setw(7) << std::setfill(' ') << std::fixed << std::setprecision(0) << value;
    return oss.str();
}

void Menus::show()
{
    menu_top();
    menu_bottom();
}

void Menus::menu_top()
{
    ImGuiIO &io = ImGui::GetIO(); (void)io;

    FrameBuffer fb = app.buffers.getBuffer();

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,ImVec2(4.0f, 16.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing,ImVec2(32.0f, 4.0f));
    {   
        ImGui::SetNextWindowSize(io.DisplaySize);
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoScrollbar;
        window_flags |= ImGuiWindowFlags_MenuBar;
        window_flags |= ImGuiWindowFlags_NoDecoration;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoCollapse;
        window_flags |= ImGuiWindowFlags_NoNav;
        window_flags |= ImGuiWindowFlags_NoBackground;
        
        ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f)); 
        ImGui::Begin("Menus", NULL, window_flags);                         

        if (ImGui::BeginMenuBar())
        {
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            draw_list->AddImage(
                (void*)(intptr_t)logo.texture,
                ImVec2(0+32, 0+8),
                ImVec2(80+32, 80+8),
                ImVec2(0, 0),
                ImVec2(1, 1)
            );
            
            ImGui::BeginDisabled();
            if(ImGui::BeginMenu("     ")){
                ImGui::EndMenu();
            }
            ImGui::EndDisabled();
            ImGui::Separator();

            if (ImGui::BeginMenu(floatToFormattedString(fb.framerate).c_str()))
            {
                
                ImGui::MenuItem("24");
                ImGui::MenuItem("30");
                ImGui::MenuItem("50");
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("   100"))
            {
                ImGui::MenuItem("100");
                ImGui::MenuItem("200");
                ImGui::MenuItem("400");
                ImGui::MenuItem("800");
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("   180°"))
            {
                if (ImGui::MenuItem("45°")) {  }
                if (ImGui::MenuItem("90°")) {  }
                if (ImGui::MenuItem("144°")) {  }
                if (ImGui::MenuItem("180°")) {  }
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu(ICON_FA_COG))
            {
                if (ImGui::MenuItem("ZEBRA")) {}
                if (ImGui::MenuItem("FOCUS")) {}
                if (ImGui::BeginMenu("HISTOGRAM"))
                { 
                    if (ImGui::MenuItem("ENABLE")) {}
                    if (ImGui::MenuItem("LUMA")) {}
                    ImGui::EndMenu();
                }
                
                if (ImGui::MenuItem("WAVE")) {}
                if (ImGui::MenuItem("FALSE")) {}
                if (ImGui::MenuItem("RGB")) {}

                if(1){
                    if (ImGui::BeginMenu("BAYER"))
                    { 
                        if (ImGui::MenuItem("SPLIT")) {}
                        ImGui::EndMenu();
                    }
                }

                if (ImGui::BeginMenu("OVERLAYS"))
                { 
                    if (ImGui::MenuItem("CROSS")) {}
                    if (ImGui::MenuItem("THIRDS")) {}
                    ImGui::EndMenu();
                }
                if (ImGui::MenuItem("DEMO")) { }
                if (ImGui::BeginMenu("ZOOM"))
                { 
                    if (ImGui::MenuItem("1x")) { }
                    if (ImGui::MenuItem("2x")) { }
                    if (ImGui::MenuItem("4x")) { }
                    if (ImGui::MenuItem("8x")) { }
                    if (ImGui::MenuItem("16x")) { }
                    ImGui::EndMenu();
                }
                ImGui::PushItemWidth(200);
                ImGui::SliderFloat("ZOOM", NULL, 0.0f, 16.0f);
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("     ---"))
            {
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("  5600k"))
            {

                ImGui::EndMenu();
            }
            ImGui::Separator();

            draw_list->AddText(app.ui24, app.ui24->FontSize, ImVec2(180, 8), IM_COL32(100, 100, 100, 255), "FPS");
            draw_list->AddText(app.ui24, app.ui24->FontSize, ImVec2(400, 8), IM_COL32(100, 100, 100, 255), "ISO");
            draw_list->AddText(app.ui24, app.ui24->FontSize, ImVec2(580, 8), IM_COL32(100, 100, 100, 255), "SHT");
            draw_list->AddText(app.ui24, app.ui24->FontSize, ImVec2(940, 8), IM_COL32(100, 100, 100, 255), "IRIS");
            draw_list->AddText(app.ui24, app.ui24->FontSize, ImVec2(1200, 8), IM_COL32(100, 100, 100, 255), "WB");

            ImGui::EndMenuBar();   
        }
        ImGui::End();
        ImGui::PopStyleColor(1);
    }
    ImGui::PopStyleVar(2);
}

void Menus::menu_bottom()
{
    ImGuiIO &io = ImGui::GetIO();
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,ImVec2(4.0f, 16.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing,ImVec2(32.0f, 4.0f));
    const ImGuiViewport *viewport = ImGui::GetMainViewport();

    // Set position to the bottom of the viewport
    ImGui::SetNextWindowPos(
        ImVec2(viewport->Pos.x,
                viewport->Pos.y + viewport->Size.y - ImGui::GetFrameHeight()));

    // Extend width to viewport width
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, ImGui::GetFrameHeight()));

    // Add menu bar flag and disable everything else
    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_MenuBar;

    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f)); 
    if (ImGui::Begin("StatusBar", nullptr, flags)) {

        if (ImGui::BeginMenuBar()) {

            // ImDrawList* draw_list = ImGui::GetWindowDrawList();
            // draw_list->AddCircleFilled(ImVec2(400, 1030), 17.0f, ImColor(1.0f, 0.0f, 0.0f), 20);
            // draw_list->AddText(ui48, ui48->FontSize, ImVec2(430, 1008), IM_COL32(255, 0, 0, 255), "REC");

            // ImGui::PushFont(ui36);
            // ImGui::PushFont(icons_font24);
            // ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            // ImGui::PopFont();
            // ImGui::PopFont();

            ImGui::Separator();
            ImGui::Text("FPS: %.1f FPS", io.Framerate);
            ImGui::Separator();
            ImGui::Text("GPU: %3.1f%%", app.stats.stat_gpu);
            ImGui::Separator();
            ImGui::Text("CPU: %3.1f%%", app.stats.stat_cpu);
            ImGui::Separator();

            // Record and photo buttons
            {
                ImDrawList* fg_draw = ImGui::GetForegroundDrawList();
                float bar_h = ImGui::GetFrameHeight();
                float btn_y = viewport->Pos.y + viewport->Size.y - bar_h * 0.5f - 10.0f;
                SharedMemoryBuffer* ctx = app.cinepiraw.get_context();

                // Red record button — filled when idle, outline when recording
                float rec_x = viewport->Pos.x + viewport->Size.x - 120.0f;
                float rec_r = 22.0f;
                if (is_recording) {
                    fg_draw->AddCircle(ImVec2(rec_x, btn_y), rec_r, IM_COL32(220, 30, 30, 255), 32, 3.0f);
                    fg_draw->AddCircle(ImVec2(rec_x, btn_y), rec_r + 2.0f, IM_COL32(180, 0, 0, 255), 32, 2.0f);
                } else {
                    fg_draw->AddCircleFilled(ImVec2(rec_x, btn_y), rec_r, IM_COL32(220, 30, 30, 230));
                    fg_draw->AddCircle(ImVec2(rec_x, btn_y), rec_r + 2.0f, IM_COL32(180, 0, 0, 255), 32, 2.0f);
                }

                // White photo button
                float photo_x = viewport->Pos.x + viewport->Size.x - 55.0f;
                float photo_r = 18.0f;
                fg_draw->AddCircleFilled(ImVec2(photo_x, btn_y), photo_r, IM_COL32(240, 240, 240, 230));
                fg_draw->AddCircle(ImVec2(photo_x, btn_y), photo_r + 2.0f, IM_COL32(160, 160, 160, 255), 32, 2.0f);

                if (io.MouseClicked[0]) {
                    float rdx = io.MousePos.x - rec_x,   rdy = io.MousePos.y - btn_y;
                    float pdx = io.MousePos.x - photo_x, pdy = io.MousePos.y - btn_y;

                    if (rdx*rdx + rdy*rdy <= rec_r*rec_r) {
                        console->info("record button hit, sending SIGUSR2 to pid {}", ctx ? ctx->procid : -1);
                        if (ctx != nullptr && ctx->procid > 0) {
                            ::kill(ctx->procid, SIGUSR2);
                            is_recording = !is_recording;
                        }
                    } else if (pdx*pdx + pdy*pdy <= photo_r*photo_r) {
                        console->info("photo button hit, sending SIGUSR1 to pid {}", ctx ? ctx->procid : -1);
                        if (ctx != nullptr && ctx->procid > 0)
                            ::kill(ctx->procid, SIGUSR1);
                    }
                }
            }

            ImGui::EndMenuBar();
        }
    ImGui::End();
    }
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(2);
}

Page *make_menus_page(Application& app){
    return new Menus(app);
}