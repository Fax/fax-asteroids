#include <iostream>
#include "assetManager.h"
#include "raylib.h"

namespace Core
{
    AssetManager::AssetManager()
    {
        InitAudioDevice();
    }
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

    void AssetManager::loadSound(std::string soundAlias, std::string path)
    {
        std::cout << "loading sound" << std::endl;
        if (m_sounds.find(soundAlias) != m_sounds.end())
        {
            // if it does, unload it and replace it with the new one.
            UnloadSound(m_sounds[soundAlias]);
        }
        Sound sound = LoadSound(path.c_str());
        m_sounds[soundAlias] = sound;
    }
    void AssetManager::updateSound()
    {
        m_aliases.erase(
            std::remove_if(
                m_aliases.begin(),
                m_aliases.end(),
                [](Sound p)
                {
                    if (!IsSoundPlaying(p))
                    {
                        UnloadSoundAlias(p);
                        return true;
                    }
                    return false;
                }),
            m_aliases.end());
    }
    void AssetManager::playSound(std::string soundAlias, int retrig)
    {
        if (m_sounds.find(soundAlias) != m_sounds.end())
        {
            if (IsSoundPlaying(m_sounds[soundAlias]))
            {
                if (retrig > 0)
                {
                    auto alias = LoadSoundAlias(m_sounds[soundAlias]);
                    m_aliases.emplace_back(alias);
                    PlaySound(alias);
                }
            }
            else
            {

                // if it does, unload it and replace it with the new one.
                PlaySound(m_sounds[soundAlias]);
            }
        }
    }

}
