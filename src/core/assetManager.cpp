#include <iostream>
#include "assetManager.h"

namespace Core
{
    void AssetManager::load(std::string textureAlias, std::string path)
    {
        // check if texture exists.
        std::cout << "loading " << std::endl;
        if (m_textures.find(textureAlias) != m_textures.end())
        {
            // if it does, unload it and replace it with the new one.
            UnloadTexture(m_textures[textureAlias]);
        }
        else
        {
            m_keys.emplace_back(textureAlias);
        }
        Texture2D text = LoadTexture(path.c_str());
        m_textures[textureAlias] = text;
    }

    Texture2D &AssetManager::getTexture(std::string textureAlias)
    {
        return m_textures[textureAlias];
    }
    Texture2D &AssetManager::getTexture(SpriteDefinition definition)
    {
        return m_textures[definition.name];
    }

    size_t AssetManager::countLoadedTextures() const
    {
        return m_textures.size();
    }

    const std::vector<std::string> &AssetManager::getKeys() const
    {
        return m_keys;
    }

}
