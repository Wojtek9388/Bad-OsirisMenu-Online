#pragma once
#include "imgui/imgui.h"
#include "imgui_custom.h"
#include <string>
#include <array>

bool windowOpen = true;
namespace osiris
{
class Backtrack
{
    public:
        void drawGUI(bool contentOnly) noexcept
        {
            if (!contentOnly) {
                ImGui::SetNextWindowSize({ 0.0f, 0.0f });
                ImGui::Begin("Backtrack", &windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
            }
            ImGui::Checkbox("Enabled", &this->enabled);
            ImGui::Checkbox("Ignore smoke", &this->ignoreSmoke);
            ImGui::Checkbox("Recoil based fov", &this->recoilBasedFov);
            ImGui::PushItemWidth(220.0f);
            ImGui::SliderInt("Time limit", &this->timeLimit, 1, 200, "%d ms");
            ImGui::PopItemWidth();
            if (!contentOnly)
                ImGui::End();
        }
    private:
        bool enabled;
        bool ignoreSmoke;
        bool recoilBasedFov;
        int timeLimit;
};

class Sound
{
    public:
        void drawGUI(bool contentOnly) noexcept
        {
            if (!contentOnly) {
                ImGui::SetNextWindowSize({ 0.0f, 0.0f });
                ImGui::Begin("Sound", &windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
                    | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
            }
        
            ImGui::PushID("Sound");
        
            // Placeholder widgets
            ImGui::SliderInt("Chicken volume", &this->ChickenVolume, 0, 200, "%d%%");
            ImGui::PushItemWidth(110.0f);
            ImGui::Combo("Category", &this->Category, "Local player\0Allies\0Enemies\0");
            ImGui::PopItemWidth();
            ImGui::SliderInt("Master volume", &this->MasterVolume, 0, 200, "%d%%");
            ImGui::SliderInt("Headshot volume", &this->HeadshotVolume, 0, 200, "%d%%");
            ImGui::SliderInt("Weapon volume", &this->WeaponVolume, 0, 200, "%d%%");
            ImGui::SliderInt("Footstep volume", &this->FootstepVolume, 0, 200, "%d%%");
        
            ImGui::PopID();
        
            if (!contentOnly)
                ImGui::End();
        }
    private:
        int ChickenVolume;
        int MasterVolume;
        int HeadshotVolume;
        int WeaponVolume;
        int FootstepVolume;

        int Category;
};

class Visuals
{
    public:
        void drawGUI(bool contentOnly) noexcept
        {
            if (!contentOnly) {
                ImGui::SetNextWindowSize({ 680.0f, 0.0f });
                ImGui::Begin("Visuals", &windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
                    | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
            }
        
            ImGui::Columns(2, nullptr, false);
            ImGui::SetColumnOffset(1, 280.0f);
        
            ImGui::Checkbox("Disable post-processing", &DisablePostProcessing);
            ImGui::Checkbox("Inverse ragdoll gravity", &InverseRagdollGravity);
            ImGui::Checkbox("No fog", &NoFog);
            ImGui::Checkbox("No 3d sky", &No3dSky);
            ImGui::Checkbox("No aim punch", &NoAimPunch);
            ImGui::Checkbox("No view punch", &NoViewPunch);
            ImGui::Checkbox("No hands", &NoHands);
        
            ImGui::NextColumn();
            ImGui::Checkbox("Zoom", &DisablePostProcessing);
            ImGui::SameLine();
            ImGui::PushID("Zoom Key");
            ImGui::Text("Hotkey");
            ImGui::PopID();
        
            ImGui::Checkbox("Thirdperson", &InverseRagdollGravity);
            ImGui::SameLine();
            ImGui::PushID("Thirdperson Key");
            ImGui::Text("Hotkey");
            ImGui::PopID();
        
            ImGui::PushItemWidth(290.0f);
            ImGui::PushID(0);
            ImGui::SliderInt("", &ThirdPersonDistance, 0, 1000, "Thirdperson distance: %d");
            ImGui::PopID();
        
            ImGui::PushID(1);
            ImGui::SliderInt("", &ViewmodelFOV, -60, 60, "Viewmodel FOV: %d");
            ImGui::PopID();
        
            ImGui::PushID(2);
            ImGui::SliderInt("", &FOV, -60, 60, "FOV: %d");
            ImGui::PopID();
        
            ImGui::PushID(3);
            ImGui::SliderInt("", &FarZ, 0, 2000, "Far Z: %d");
            ImGui::PopID();
        
            ImGui::PushID(4);
            ImGui::SliderInt("", &FlashReduction, 0, 100, "Flash reduction: %d%%");
            ImGui::PopID();
        
            ImGui::PushID(5);
            ImGui::SliderFloat("", &Brightness, 0.0f, 1.0f, "Brightness: %.2f");
            ImGui::PopID();
            ImGui::PopItemWidth();
        
            ImGui::PushID(6);
            ImGui::Checkbox("", &dummySkybox.enabled);
            ImGui::PopID();
            ImGui::SameLine();
            ImGui::Combo("Skybox", &dummySkybox.skybox, "Sky1\0Sky2\0Sky3\0");
        
            ImGui::Text("World color placeholder"); // dummyColor1
            ImGui::Text("Sky color placeholder");   // dummyColor2
        
            ImGui::Checkbox("Deagle spinner", &NoFog);
        
            ImGui::Combo("Screen effect", &ThirdPersonDistance, "None\0Drone cam\0Underwater\0Healthboost\0Dangerzone\0");
            ImGui::Combo("Hit effect", &ViewmodelFOV, "None\0Drone cam\0Underwater\0Healthboost\0Dangerzone\0");
            ImGui::SliderFloat("Hit effect time", &HitEffectTime, 0.1f, 1.5f, "%.2fs");
            ImGui::Combo("Hit marker", &FOV, "None\0Default (Cross)\0");
            ImGui::SliderFloat("Hit marker time", &Brightness, 0.1f, 1.5f, "%.2fs");
        
            ImGui::Columns(1);
        
            if (!contentOnly)
                ImGui::End();
        }
    private:
        bool DisablePostProcessing;
        bool InverseRagdollGravity;
        bool NoFog;
        bool No3dSky;
        bool NoAimPunch;
        bool NoViewPunch;
        bool NoHands;

        int ThirdPersonDistance;
        int ViewmodelFOV;
        int FOV;
        int FlashReduction;
        int FarZ;
        
        float Brightness;
        float HitEffectTime;

        struct { bool enabled; int skybox; } dummySkybox{ true, 0 };
        struct { float color[4]; bool enabled; } dummyColor1{{1,0,0,1}, true}, dummyColor2{{0,1,0,1}, true};
};

class Glow
{
    public:
        void drawGUI(bool contentOnly) noexcept
        {
            if (!contentOnly) {
                if (!windowOpen)
                    return;
            
                ImGui::SetNextWindowSize({ 450.0f, 0.0f });
                ImGui::Begin("Glow", &windowOpen,
                    ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoScrollbar |
                    ImGuiWindowFlags_NoScrollWithMouse
                );
            }
        
            // Category selection
            int currentCategory{ 0 };
            ImGui::PushItemWidth(110.0f);
            ImGui::PushID(0);
        
            constexpr std::array categories{
                "Allies", "Enemies", "Planting", "Defusing",
                "Local Player", "Weapons", "C4", "Planted C4",
                "Chickens", "Defuse Kits", "Projectiles", "Hostages", "Ragdolls"
            };
        
            ImGui::Combo("", &currentCategory, categories.data(), categories.size());
            ImGui::PopID();
        
        
            // First 4 categories have types (All / Visible / Occluded)
            if (currentCategory <= 3) {
                ImGui::SameLine();
                int currentType{ 0 };
                ImGui::PushID(1);
                ImGui::Combo("", &currentType, "All\0Visible\0Occluded\0");
                ImGui::PopID();
        
            // Main settings
            ImGui::SameLine();
            ImGui::Checkbox("Enabled", &this->enabled);
            ImGui::Separator();
        
            ImGui::Columns(2, nullptr, false);
            ImGui::SetColumnOffset(1, 150.0f);
        
            ImGui::Checkbox("Health based", &this->healthBased);
            ImGui::ColorPicker3("Color", &this->currentItem);
        
            ImGui::NextColumn();
            ImGui::SetNextItemWidth(100.0f);
            ImGui::Combo("Style", &this->style, "Default\0Rim3d\0Edge\0Edge Pulse\0");
        
            ImGui::Columns(1);
        
            if (!contentOnly)
                ImGui::End();
            }
        };
    private:
        bool enabled;
        bool healthBased;
        float currentItem;
        int style;
};
};

class FeaturesClass
{
    public:
        osiris::Backtrack Backtrack;
        osiris::Sound Sound;
        osiris::Visuals Visuals;
        osiris::Glow Glow;
};

inline void RenderOsiris(FeaturesClass* features) {
    // window flags for Osiris menu style
    constexpr auto windowFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

    ImGui::Begin("Osiris", nullptr, windowFlags | ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyScroll)) {

        // ===== Aimbot Tab =====
        if (ImGui::BeginTabItem("Aimbot")) {
            bool aimbotEnabled = false;
            int bone = 0;
            float fov = 0.0f, smooth = 1.0f;
            int minDamage = 0;

            ImGui::Checkbox("Enable Aimbot", &aimbotEnabled);
            ImGui::Combo("Bone", &bone, "Nearest\0Best damage\0Head\0Neck\0Sternum\0Chest\0Stomach\0Pelvis\0");
            ImGui::SliderFloat("Fov", &fov, 0.0f, 255.0f);
            ImGui::SliderFloat("Smooth", &smooth, 1.0f, 100.0f);
            ImGui::InputInt("Min Damage", &minDamage);

            ImGui::EndTabItem();
        }

        // ===== Triggerbot Tab =====
        if (ImGui::BeginTabItem("Triggerbot")) {
            bool triggerEnabled = false;
            int hitgroup = 0;
            int shotDelay = 0;
            int minDamage = 0;

            ImGui::Checkbox("Enable Triggerbot", &triggerEnabled);
            ImGui::Combo("Hitgroup", &hitgroup, "All\0Head\0Chest\0Stomach\0Left arm\0Right arm\0Left leg\0Right leg\0");
            ImGui::SliderInt("Shot Delay", &shotDelay, 0, 250);
            ImGui::InputInt("Min Damage", &minDamage);

            ImGui::EndTabItem();
        }

        // ===== Backtrack Tab =====
        if (ImGui::BeginTabItem("Backtrack")) {
            features->Backtrack.drawGUI(true);
            ImGui::EndTabItem();
        }

        // ===== Glow Tab =====
        if (ImGui::BeginTabItem("Glow")) {
            features->Glow.drawGUI(true);
            ImGui::EndTabItem();
        }

        // ===== Chams Tab =====
        if (ImGui::BeginTabItem("Chams")) {
            bool chamsEnabled = false;
            float color[3] = { 1.0f, 1.0f, 1.0f };

            ImGui::Checkbox("Enable Chams", &chamsEnabled);
            ImGui::ColorEdit3("Color", color);

            ImGui::EndTabItem();
        }

        // ===== ESP Tab =====
        if (ImGui::BeginTabItem("ESP")) {
            ImGui::Text("ESP settings placeholder");
            ImGui::EndTabItem();
        }

        // ===== Visuals Tab =====
        if (ImGui::BeginTabItem("Visuals")) {
            features->Visuals.drawGUI(true);
            ImGui::EndTabItem();
        }

        // ===== Inventory Changer Tab =====
        if (ImGui::BeginTabItem("Inventory Changer")) {
            ImGui::Text("Inventory Changer placeholder");
            ImGui::EndTabItem();
        }

        // ===== Sound Tab =====
        if (ImGui::BeginTabItem("Sound")) {
            features->Sound.drawGUI(true);
            ImGui::EndTabItem();
        }

        // ===== Style Tab =====
        if (ImGui::BeginTabItem("Style")) {
            int menuStyle = 0;
            int menuColors = 0;

            ImGui::Combo("Menu Style", &menuStyle, "Classic\0One window\0");
            ImGui::Combo("Menu Colors", &menuColors, "Dark\0Light\0Classic\0Custom\0");

            ImGui::EndTabItem();
        }

        // ===== Misc Tab =====
        if (ImGui::BeginTabItem("Misc")) {
            ImGui::Text("Misc settings placeholder");
            ImGui::EndTabItem();
        }

        // ===== Config Tab =====
        if (ImGui::BeginTabItem("Config")) {
            char configName[64] = "";
            ImGui::InputText("Config Name", configName, IM_ARRAYSIZE(configName));
            ImGui::Button("Load");
            ImGui::SameLine();
            ImGui::Button("Save");
            ImGui::SameLine();
            ImGui::Button("Delete");
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}
