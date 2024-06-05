#pragma once
#include <fstream>
#include <string>
#include <unordered_map>

#include "json/json.hpp"
#include "raylib.h"

using json = nlohmann::json;

struct SpriteSheetConfig
{
    Texture2D texture;
    int frameWidth;
    int frameHeight;
    int frameCount;
};

class TextureManager
{
public:
    static void LoadConfig(const std::string &filename)
    {
        std::ifstream file(filename);
        json config;
        file >> config;

        for (auto &element : config.items())
        {
            std::string key = element.key();
            auto &value = element.value();
            SpriteSheetConfig sheetConfig;
            sheetConfig.texture = ::LoadTexture(value["texture"].get<std::string>().c_str());
            sheetConfig.frameWidth = value["frame_width"];
            sheetConfig.frameHeight = value["frame_height"];
            sheetConfig.frameCount = value["frame_count"];
            spriteSheets[key] = sheetConfig;
        }
    }

    static SpriteSheetConfig GetSpriteSheetConfig(const std::string &key)
    {
        return spriteSheets[key];
    }

    static void UnloadAllTextures()
    {
        for (auto &pair : spriteSheets)
        {
            ::UnloadTexture(pair.second.texture);
        }
        spriteSheets.clear();
    }

private:
    static std::unordered_map<std::string, SpriteSheetConfig> spriteSheets;
};

std::unordered_map<std::string, SpriteSheetConfig> TextureManager::spriteSheets;
