#include "pch.h"

#include "Menu.h"

#include "Bejeweled.h"
#include "Hooks.h"

void Menu::Setup() {
  auto& style = ImGui::GetStyle();
  auto& colors = style.Colors;
  colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(1.00f, 0.75f, 0.50f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 0.75f, 0.50f, 1.00f);
  colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 0.90f, 0.73f, 1.00f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.65f, 0.58f, 0.40f, 0.40f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.66f, 0.59f, 0.47f, 0.77f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.82f, 0.51f, 0.25f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.72f, 0.45f, 0.19f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.81f, 0.55f, 0.32f, 0.25f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.82f, 0.51f, 0.25f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.38f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.76f, 0.53f, 0.24f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.50f, 0.35f, 0.17f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.77f, 0.00f, 0.77f, 1.00f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.77f, 0.00f, 0.77f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.77f, 0.00f, 0.77f, 0.78f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.76f, 0.46f, 0.80f, 0.60f);
  colors[ImGuiCol_Button] = ImVec4(0.82f, 0.52f, 0.25f, 1.00f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.85f, 0.63f, 0.34f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.77f, 0.00f, 0.77f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.82f, 0.51f, 0.25f, 0.31f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.85f, 0.62f, 0.34f, 1.00f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.94f, 0.48f, 0.94f, 1.00f);
  colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  colors[ImGuiCol_Tab] = ImVec4(0.76f, 0.80f, 0.84f, 0.93f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  colors[ImGuiCol_TabActive] = ImVec4(0.60f, 0.73f, 0.88f, 1.00f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.92f, 0.93f, 0.94f, 0.99f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.74f, 0.82f, 0.91f, 1.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void Menu::Render() {
  ImGui::Begin("Bejeweled Mods");

  ImGui::TextWrapped("Use this menu to control in-game cheats for Bejeweled 3");
  ImGui::Text("Made by Razzile");

  ImGui::Separator();

  ImGui::Checkbox("Swaps always succeed", &Hooks::settings.swapAlwaysSucceeds);

  // Piece flags options
  {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
    ImGui::BeginChild("ChildR", ImVec2(0, 260), true, window_flags);
    if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("Piece Editing")) {
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }

    ImGui::TextWrapped(
        "Editing this option will change the 'type' of a piece when you click "
        "on it in-game.");

    static int e = -1;
    ImGui::RadioButton("Default", &e, -1);
    ImGui::RadioButton("Normal", &e,
                       static_cast<int>(Sexy::Piece::PieceFlags::Normal));
    ImGui::RadioButton("Bomb", &e,
                       static_cast<int>(Sexy::Piece::PieceFlags::Bomb));
    ImGui::RadioButton("Hypercube", &e,
                       static_cast<int>(Sexy::Piece::PieceFlags::Hypercube));
    ImGui::RadioButton("Electric", &e,
                       static_cast<int>(Sexy::Piece::PieceFlags::Electric));
    ImGui::RadioButton("Big Points", &e,
                       static_cast<int>(Sexy::Piece::PieceFlags::BigPoints));
    ImGui::RadioButton("Time Bomb", &e,
                       static_cast<int>(Sexy::Piece::PieceFlags::TimeBomb));
    ImGui::RadioButton("Butterfly", &e,
                       static_cast<int>(Sexy::Piece::PieceFlags::Butterfly));
    ImGui::RadioButton("Locked Gem", &e,
                       static_cast<int>(Sexy::Piece::PieceFlags::LockedGem));
    ImGui::RadioButton("Last Hurrah", &e,
                       static_cast<int>(Sexy::Piece::PieceFlags::LastHurrah));
    ImGui::RadioButton("Mystery Gem", &e,
                       static_cast<int>(Sexy::Piece::PieceFlags::MysteryGem));
    ImGui::RadioButton("Supernova", &e,
                       static_cast<int>(Sexy::Piece::PieceFlags::Supernova));

    Hooks::settings.pieceFlags = e;

    ImGui::EndChild();
    ImGui::PopStyleVar();
  }

  ImGui::End();
}
