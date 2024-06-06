#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "raylib.h"
namespace Core
{
    // what if it's a sprite sheet?
    // and who cares right now?
    struct SpriteDefinition
    {
        std::string name;
        float height;
        float width;
    };
    // You can't remove assets from AssetManager
    // the reason?
    // WHY WOULD YOU REMOVE DATA AT RUNTIME?
    // If you need to add a "scope" to some asset, a scene for example,
    // just create a new asset manager (inherit) and manage the unload procedure yourself
    class AssetManager
    {
    public:
        void load(std::string textureAlias, std::string path);
        Texture2D &getTexture(std::string textureAlias);
        Texture2D &getTexture(SpriteDefinition definition);
        size_t countLoadedTextures() const;
        const std::vector<std::string> &getKeys() const;
    private:
        std::vector<std::string> m_keys;
        std::unordered_map<std::string, Texture2D> m_textures;
    };
}
