#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include<iostream>
#include<fstream>
#include<SFML/Audio.hpp>
#include "AnimationData.h"


// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)

//singleton


class Resources
{
private:
	std::vector<std::string> m_levels;
	std::vector<sf::Texture> m_textures;
	std::vector<sf::Sound> m_sounds;
	std::vector<sf::SoundBuffer> m_buffers;
	std::vector<sf::Font> m_Fonts;
	std::vector<AnimationData> m_animationData;
	std::vector<std::string> m_playersNames;
	int m_levelTime;
	sf::Texture m_texture;
	sf::Font m_font;

	Resources();
	Resources(const Resources&) = delete;
	Resources& operator = (const Resources&) = delete;

	
	std::vector<std::string> readNamesVector(const char[]) const;
	std::vector<sf::Texture> getTexturesVector(const std::vector<std::string>&)const;
	std::vector<sf::Sound> fillSoundsVector(const std::vector<sf::SoundBuffer>& buffer)const;
	std::vector<sf::SoundBuffer> fillBufferVector(const std::vector<std::string>&)const;
	

public:
	enum Objects
	{
		FirstPlayer,
		SecondPlayer,
		EnemyBear,
		Heart,
		Coin,
		EnemyBat,
		Max
	};
	//void playMusic();
	//void playSound(const int index);
	static Resources& instance();
	~Resources() = default;
	
	const std::vector<sf::Texture>& getTextures() const;
	//const sf::Texture& getTexture(const int index) const;
	//const std::vector<sf::Font>& getFonts() const;
	const sf::Font& getFont() const;
	const std::string& getLevel(const int index) const;
	const std::vector<std::string> getPlayers() const;
	void saveCurrentLevel(const int);
	int getCurrentLevel()const;

	std::vector<std::string>buildMap(const int);
	const AnimationData& animationData(Objects object) { return m_animationData[object]; }


};